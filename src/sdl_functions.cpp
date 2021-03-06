#include "../includes/duel.h"

using namespace std;

void			SDL_init_window(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
			failure_exit_program("Initialization SDL WINDOW", sdl);
	SDL_get_desktop_display_mode(sdl, 0, &sdl->display);
	sdl->disp = {0, 0, sdl->display.w, sdl->display.h};
	if ((sdl->window = SDL_CreateWindow("SUCH AMAZING TETRIS, SUCH WOW",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sdl->disp.w,
				sdl->disp.h, SDL_WINDOW_SHOWN)) == NULL)
		failure_exit_program("Creating sdl->window", sdl);
	while ((sdl->disp.w % 720) % 8 != 0)
		sdl->disp.w--;
	while ((sdl->disp.h % 480) % 8 != 0)
		sdl->disp.h--;
}

void			SDL_init_renderer(t_sdl *sdl)
{
	if ((sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)) == NULL)
		failure_exit_program("Creating Window Renderer", sdl);
}

SDL_Texture		*SDL_create_texture(t_sdl *sdl, SDL_Texture *texture, int width,
				int height)
{
	if ((texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, width, height)) == NULL)
		failure_exit_program("Creating texture", sdl);
	return (texture);
}

void			SDL_apply_color_to_renderer(SDL_Color rgba, t_sdl *sdl)
{
	if ((SDL_SetRenderDrawColor(sdl->renderer, rgba.r, rgba.g, rgba.b, rgba.a))
			!= 0)
		failure_exit_program("Rendering Color", sdl);
}

void			SDL_init_img(void)
{
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		cout << "Failure Initializing IMAGES "<< IMG_GetError() << endl;
}

void			SDL_init_audio(void)
{
	if ((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0))
		cout << "Failure Initializing Audio " << Mix_GetError() << endl;
}

void			SDL_get_desktop_display_mode(t_sdl *sdl, int option,
				SDL_DisplayMode *display)
{
	if (SDL_GetDesktopDisplayMode(option, display) != 0)
		failure_exit_program("Getting display mode", sdl);
}

SDL_Texture		*SDL_load_texture(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, string path)
{
	if ((texture = IMG_LoadTexture(renderer, path.c_str())) == NULL)
		failure_exit_program("Loading Image on Texture", sdl);
	return (texture);
}

void			SDL_render_clear(t_sdl *sdl, SDL_Renderer *renderer)
{
	if ((SDL_RenderClear(renderer)) != 0)
		failure_exit_program("Clearing Render With Color", sdl);
}

void			SDL_render_copy(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest)
{
	if (SDL_RenderCopy(renderer, texture, src, dest) != 0)
		failure_exit_program("Rendering Copy Of Texture" , sdl);
}

void			SDL_render_target(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture)
{
	if (SDL_SetRenderTarget(renderer, texture) != 0)
		failure_exit_program("Setting Texture as Render Target", sdl);
}

void			SDL_query_texture(t_sdl *sdl, SDL_Texture *texture, Uint32 *format,
				int *access, int *w, int *h)
{
	if (SDL_QueryTexture(texture, format, access, w, h) != 0)
		failure_exit_program("Query Texture", sdl);
}
