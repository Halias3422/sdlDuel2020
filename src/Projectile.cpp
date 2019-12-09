#include "../includes/duel.h"

using namespace std;

Projectile::Projectile(t_sdl *sdl, string path, int pos_x, int pos_y, int new_direction)
{
	texture = SDL_load_texture(sdl, sdl->renderer, texture, path);
	if (new_direction == -1)
		dst.x = pos_x - 4;
	else if (new_direction == 1)
		dst.x = pos_x + 16;
	dst.y = pos_y + 8;
	dst.w = 4;
	dst.h = 4;
	direction = new_direction;
}

int			Projectile::get_x_pos(void)
{
	return (dst.x);
}

int			Projectile::get_y_pos(void)
{
	return (dst.y);
}


void		Projectile::print_projectile_on_screen(t_sdl *sdl)
{
	SDL_render_copy(sdl, sdl->renderer, texture, NULL, &dst);
	dst.x += 10 * direction;

}

void		moving()
{

}

Projectile::~Projectile()
{

}
