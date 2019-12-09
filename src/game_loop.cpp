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
	if (yellow->get_projectiles_list_size() > 0)
		yellow->print_projectiles(sdl);
	SDL_render_target(sdl, sdl->renderer, NULL);
	SDL_render_copy(sdl, sdl->renderer, sdl->buffer, NULL, &sdl->disp);
	SDL_RenderPresent(sdl->renderer);
}

int			get_keyboard_state(t_sdl *sdl, Player *yellow, Player *red)
{
	const Uint8 *state;
	SDL_Event	event;
	int		game_over = 0;

		state = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		if (state[SDL_SCANCODE_ESCAPE])
			game_over = 1;
		if (state[SDL_SCANCODE_W])
			yellow->jumping();
		if (state[SDL_SCANCODE_A])
			yellow->set_x_pos(-1, red);
		if (state[SDL_SCANCODE_D])
			yellow->set_x_pos(1, red);
		if (state[SDL_SCANCODE_KP_8])
			red->jumping();
		if (state[SDL_SCANCODE_KP_4])
			red->set_x_pos(-1, yellow);
		if (state[SDL_SCANCODE_KP_6])
			red->set_x_pos(1, yellow);
		if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_j)
			{
				yellow->shooting(sdl, -1);
				yellow->print_list();
			}
		}
		return (game_over);
}

void		game_loop(t_sdl *sdl, Player *yellow, Player *red)
{
	int		game_over = 0;

	set_window_background(sdl);
	while (game_over == 0)
	{
		print_on_screen(sdl, yellow, red);
		yellow->moving();
		red->moving();
		game_over = get_keyboard_state(sdl, yellow, red);
		SDL_Delay(16);
	}
}
