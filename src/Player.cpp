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

void	Player::set_x_pos(int direction, Player *other)
{
	int	other_x = other->get_x_pos();

	dst.x+= 5 * direction;
	if (dst.x + dst.w > 720)
		dst.x = 704;
	if (dst.x < 0)
		dst.x = 0;
	if (dst.x + dst.w > other_x && dst.x < other_x)
		dst.x = other_x - dst.w;
	if (dst.x > other_x && dst.x < other_x + other->get_width())
		dst.x = other_x + other->get_width();
}

void	Player::printing(t_sdl *sdl)
{
	SDL_render_copy(sdl, sdl->renderer, texture, NULL, &dst);
}

void	Player::moving(void)
{
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
	Projectile	projectile(sdl, "img/png/bullet.png", dst.x, dst.y, direction);

	projectiles.push_back(projectile);
}

void	Player::print_projectiles(t_sdl *sdl)
{
	list <Projectile>::iterator it;
	for (it = projectiles.begin(); it != projectiles.end(); ++it)
		it->print_projectile_on_screen(sdl);
}

void	Player::print_list(void)
{
	list <Projectile> :: iterator it;
	for (it = projectiles.begin(); it != projectiles.end(); ++it)
		cout <<  "elem x = " << it->get_x_pos() << "y = " << it->get_y_pos() << endl;
	cout << endl;
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}
