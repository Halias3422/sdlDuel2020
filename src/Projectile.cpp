#include "../includes/duel.h"

using namespace std;

Projectile::Projectile(t_sdl *sdl, string path)
{
	texture = SDL_load_texture(sdl, sdl->renderer, texture, path);
}

void		moving()
{

}

Projectile::~Projectile()
{

}
