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
	SDL_get_desktop_display_mode(sdl, 0, &sdl->display);
	sdl->buffer = SDL_create_texture(sdl, sdl->buffer, 720, 480);
	sdl->background = SDL_load_texture(sdl, sdl->renderer, sdl->background,
	"img/png/general_background.png");
	SDL_render_clear(sdl, sdl->renderer);

	SDL_Rect	dst;
	SDL_render_clear(sdl, sdl->renderer);
	SDL_SetRenderTarget(sdl->renderer, sdl->buffer);
	SDL_render_clear(sdl, sdl->renderer);
   SDL_QueryTexture(sdl->background, NULL, NULL, &dst.w, &dst.h);
   dst.x = 0;
   dst.y = 0;
	SDL_render_copy(sdl, sdl->renderer, sdl->background, NULL, &dst);
	SDL_SetRenderTarget(sdl->renderer, NULL);
	SDL_render_copy(sdl, sdl->renderer, sdl->buffer, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
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

void		set_window_background(t_sdl *sdl)
{
(void)sdl;	
}

int			main(void)
{
	t_sdl	sdl;

	init_sdl(&sdl);
	set_window_background(&sdl);
	SDL_Delay(1000);
	clean_sdl_struct(&sdl);
	return (0);
}
