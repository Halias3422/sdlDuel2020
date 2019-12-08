#ifndef DUEL_H
# define DUEL_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*buffer;
	SDL_Texture		*background;
	SDL_DisplayMode	display;
}					t_sdl;

// MAIN

void			failure_exit_program(std::string error, t_sdl *sdl);
void			clean_sdl_struct(t_sdl *sdl);

// SDL_FUNCTIONS

void			SDL_init_window(t_sdl *sdl);
void			SDL_init_window(t_sdl *sdl);
void			SDL_init_renderer(t_sdl *sdl);
void			SDL_apply_color_to_renderer(SDL_Color rgba, t_sdl *sdl);
void			SDL_init_img(void);
void			SDL_init_audio(void);
void			SDL_get_desktop_display_mode(t_sdl *sdl, int option,
				SDL_DisplayMode *display);
void			SDL_render_copy(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest);
void			SDL_render_clear(t_sdl *sdl, SDL_Renderer *renderer);
SDL_Texture		*SDL_create_texture(t_sdl *sdl, SDL_Texture *texture, int width,
				int height);
SDL_Texture		*SDL_load_texture(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, std::string path);



#endif
