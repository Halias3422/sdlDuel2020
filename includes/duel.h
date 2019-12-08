#ifndef DUEL_H
# define DUEL_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>

typedef struct s_sdl	t_sdl;

class Player
{
	private:
		std::string name;
		SDL_Texture	*texture;
		int			hp = 100;
		int			velocity = 0;
		bool		is_grounded = false;
		SDL_Rect	dst;

	public:
		Player(t_sdl *sdl, std::string new_name, std::string new_texture,
				int pos_x, int pos_y);
		std::string	get_name(void);
		int			get_x_pos(void);
		int			get_y_pos(void);
		int			get_velocity(void);
		void		set_x_pos(int direction);
		void		printing(t_sdl *sdl);
		void		moving(void);
		void		jumping(void);
		~Player();
};

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*buffer;
	SDL_Texture		*background;
	SDL_Rect		background_dst;
	SDL_Texture		*ground;
	SDL_Rect		ground_dst;
	SDL_DisplayMode	display;
}					t_sdl;

// MAIN

void			failure_exit_program(std::string error, t_sdl *sdl);
void			clean_sdl_struct(t_sdl *sdl);

// GAME_LOOP

void			game_loop(t_sdl *sdl, Player *yellow, Player *red);

// SDL_FUNCTIONS

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
void			SDL_render_copy(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest);
void			SDL_render_target(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture);
SDL_Texture		*SDL_create_texture(t_sdl *sdl, SDL_Texture *texture, int width,
		int height);
SDL_Texture		*SDL_load_texture(t_sdl *sdl, SDL_Renderer *renderer,
		SDL_Texture *texture, std::string path);
void			SDL_query_texture(t_sdl *sdl, SDL_Texture *texture, Uint32 *format,
				int *access, int *w, int *h);



#endif
