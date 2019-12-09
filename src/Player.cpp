#include "../includes/duel.h"

using namespace std;


Player::Player(t_sdl *sdl, string new_name, string new_texture, int pos_x, int pos_y)
{
	name = new_name;
	texture = SDL_load_texture(sdl, sdl->renderer, texture, new_texture);
	dst.x = pos_x;
	dst.y = pos_y;
	SDL_query_texture(sdl, texture, NULL, NULL, &dst.w, &dst.h);
}

string	Player::get_name(void)
{
	return (name);
}

int		Player::get_x_pos(void)
{
	return (dst.x);
}

int		Player::get_y_pos(void)
{
	return (dst.y);
}

int		Player::get_width(void)
{
	return (dst.w);
}

int		Player::get_projectiles_list_size(void)
{
	return (projectiles.size());
}

int		Player::get_health(void)
{
	return (hp);
}

void		Player::update_last_shot(void)
{
	last_shot = SDL_GetTicks();
}

void	Player::set_x_pos(int direction, Player *other)
{
	int	other_x = other->get_x_pos();
	int	other_y = other->get_y_pos();

	dst.x+= 5 * direction;
	if (dst.x + dst.w > 720)
		dst.x = 704;
	if (dst.x < 0)
		dst.x = 0;
	if (dst.x + dst.w > other_x && dst.x < other_x && dst.y + dst.h > other_y &&
	dst.y + dst.h <= other_y + dst.h)
		dst.x = other_x - dst.w;
	if (dst.x > other_x && dst.x < other_x + other->get_width() && dst.y +
	dst.h > other_y && dst.y + dst.h <= other_y + dst.h)
		dst.x = other_x + other->get_width();
}

void	Player::printing(t_sdl *sdl)
{
	SDL_render_copy(sdl, sdl->renderer, texture, NULL, &dst);
}

void	Player::moving(Player *other)
{
	int	other_y = other->get_y_pos();
	int	other_x = other->get_x_pos();

	if (is_grounded == true && dst.y != 416 - 32 && !(((dst.x + dst.w >= other_x
	&& dst.x + dst.w <= other_x + dst.w) ||
	(dst.x >=other_x && dst.x <= other_x + dst.w)) && dst.y + dst.h == other_y))
		is_grounded = false;
	if (is_grounded == true)
		return ;
	dst.y+= 1.5 * velocity / 2;
	velocity += 1;
	if (velocity == 21)
		velocity = 20;
	if (dst.y >= 416 - 32)
	{
		dst.y = 416 - 32;
		is_grounded = true;
	}
	if (((dst.x + dst.w >= other_x && dst.x + dst.w <= other_x + dst.w) ||
	(dst.x >=other_x && dst.x <= other_x + dst.w)) && dst.y + dst.h > other_y &&
	dst.y + dst.h <= other_y + dst.h)
		dst.y = other_y - dst.h;
	if (((dst.x + dst.w >= other_x && dst.x + dst.w <= other_x + dst.w) ||
	(dst.x >=other_x && dst.x <= other_x + dst.w)) && dst.y + dst.h == other_y)
		is_grounded = true;
}

void	Player::jumping(void)
{
	if (is_grounded == false)
		return ;
	is_grounded = false;
	velocity = -20;
}

void	Player::shooting(t_sdl *sdl, int direction)
{
	if (SDL_GetTicks() < last_shot + 600)
		return ;
	Projectile	projectile(sdl, "img/png/bullet.png", dst.x, dst.y, direction);

	last_shot = SDL_GetTicks();
	projectiles.push_back(projectile);
}

void	Player::loose_life(t_sdl *sdl)
{
	hp -= 20;
	string path = "img/png/" + name + "_player_hurt_" + to_string((100 - hp) / 20) + ".png";
	SDL_DestroyTexture(texture);
	if (hp == 0)
		reset(sdl);
	else
		texture = SDL_load_texture(sdl, sdl->renderer, texture, path);
}

void	Player::reset(t_sdl *sdl)
{
	SDL_Delay(100);
	hp = 100;
	texture = SDL_load_texture(sdl, sdl->renderer, texture, "img/png/" + name + "_player.png");
	velocity = 0;
	is_grounded = false;
	last_shot = 0;
	srand(time(NULL));
	dst.x = rand() % 705;
	dst.y = 100;
}

int		Player::check_collision_bullet(t_sdl *sdl, Player *other, list <Projectile>::iterator bullet)
{
	int	other_x = other->get_x_pos();
	int	other_y = other->get_y_pos();
	int	bullet_x = bullet->get_x_pos();
	int	bullet_y = bullet->get_y_pos();

	if (bullet_x + 4 >= other_x && bullet_x < other_x + dst.w && bullet_y + 4
			>= other_y && bullet_y < other_y + dst.h)
	{
		other->loose_life(sdl);
		return (1);
	}
	return (0);
}

void	Player::print_projectiles(t_sdl *sdl, Player *other)
{
	list <Projectile>::iterator it;
	list <Projectile>::iterator tmp;

	it = projectiles.begin();
	while (it != projectiles.end())
	{
		it->print_projectile_on_screen(sdl);
		if (it->get_x_pos() > sdl->disp.w || it->get_x_pos() < -4 || check_collision_bullet(sdl, other, it))
		{
			tmp = next(it, 1);
			projectiles.erase(it);
			it = tmp;
		}
		it++;
	}
}

void	Player::print_list(void)
{
	cout << "entering list" << endl;
	list <Projectile> :: iterator it;
	for (it = projectiles.begin(); it != projectiles.end(); ++it)
		cout <<  "elem x = " << it->get_x_pos() << "y = " << it->get_y_pos() << endl;
	cout << endl;
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}
