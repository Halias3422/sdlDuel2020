#include "../includes/duel.h"

using namespace std;

void			init_sdl(t_sdl *sdl)
{
	sdl->window = NULL;
	sdl->renderer = NULL;
	sdl->background = NULL;
	SDL_init_window(sdl);
	SDL_init_renderer(sdl);
	SDL_init_audio();
	SDL_SetRenderDrawBlendMode(sdl->renderer, SDL_BLENDMODE_BLEND);
	SDL_init_img();
	sdl->buffer = SDL_create_texture(sdl, sdl->buffer, 720, 480);
	sdl->background = SDL_load_texture(sdl, sdl->renderer, sdl->background,
	"img/png/general_background.png");
	SDL_query_texture(sdl, sdl->background, NULL, NULL, &sdl->background_dst.w,
			&sdl->background_dst.h);
	sdl->background_dst.x = 0;
	sdl->background_dst.y = 0;
	sdl->ground = SDL_load_texture(sdl, sdl->renderer, sdl->ground,
	"img/png/ground.png");
	SDL_query_texture(sdl, sdl->ground, NULL, NULL, &sdl->ground_dst.w,
			&sdl->ground_dst.h);
	sdl->ground_dst.x = 0;
	sdl->ground_dst.y = 416;
}

void			clean_sdl_struct(t_sdl *sdl)
{
	SDL_DestroyTexture(sdl->background);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

void			failure_exit_program(string error, t_sdl *sdl)
{
	cout << "ERROR " << error << " (" << SDL_GetError() << ")" << endl;
	if (!sdl)
		exit(EXIT_FAILURE);
	clean_sdl_struct(sdl);
	exit(EXIT_FAILURE);
}

int			main(void)
{
	t_sdl	sdl;

	init_sdl(&sdl);
	Player	yellow(&sdl, "yellow", "img/png/yellow_player.png", 50, 100);
	Player	red(&sdl, "red", "img/png/red_player.png", 500, 100);
	game_loop(&sdl, &yellow, &red);
	clean_sdl_struct(&sdl);
	return (0);
}
