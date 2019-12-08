#include "../includes/duel.h"

using namespace std;

void		set_window_background(t_sdl *sdl)
{
	SDL_render_clear(sdl, sdl->renderer);
	SDL_render_target(sdl, sdl->renderer, sdl->buffer);
	SDL_render_copy(sdl, sdl->renderer, sdl->background, NULL, &sdl->background_dst);
	SDL_render_target(sdl, sdl->renderer, NULL);
	SDL_render_copy(sdl, sdl->renderer, sdl->buffer, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
}

void		print_on_screen(t_sdl *sdl, Player *yellow, Player *red)
{
	SDL_render_clear(sdl, sdl->renderer);
	SDL_render_target(sdl, sdl->renderer, sdl->buffer);
	SDL_render_clear(sdl, sdl->renderer);
	SDL_render_copy(sdl, sdl->renderer, sdl->background, NULL, &sdl->background_dst);
	SDL_render_copy(sdl, sdl->renderer, sdl->ground, NULL, &sdl->ground_dst);
	yellow->printing(sdl);
	red->printing(sdl);
	SDL_render_target(sdl, sdl->renderer, NULL);
	SDL_render_copy(sdl, sdl->renderer, sdl->buffer, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
}

void		game_loop(t_sdl *sdl, Player *yellow, Player *red)
{
	int		game_over = 0;
	const Uint8	*state;

	set_window_background(sdl);
	while (game_over == 0)
	{
		print_on_screen(sdl, yellow, red);
		yellow->moving();
		state = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		if (state[SDL_SCANCODE_ESCAPE])
			game_over = 1;
		if (state[SDL_SCANCODE_SPACE])
			yellow->jumping();
		if (state[SDL_SCANCODE_A])
			yellow->set_x_pos(-1);
		if (state[SDL_SCANCODE_D])
			yellow->set_x_pos(1);
		SDL_Delay(16);
	}
}
