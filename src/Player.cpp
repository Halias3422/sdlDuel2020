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

void	Player::set_x_pos(int direction)
{
	dst.x+= 5 * direction;
}

void	Player::printing(t_sdl *sdl)
{
	SDL_render_copy(sdl, sdl->renderer, texture, NULL, &dst);
}

void	Player::moving(void)
{
	if (is_grounded == true)
		return ;
	dst.y+= 1.5 * velocity;
	velocity += 1;
	if (velocity == 16)
		velocity = 15;
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
	velocity = -15;
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}
