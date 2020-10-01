#include "../include/renderWindow.h"

renderWindow::renderWindow(const char* title, int w, int h)
	:window(NULL),renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if (window == NULL) { LOG_FATAL("WINDOW FAILED TO INIT: {0}", SDL_GetError()); }
	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) { LOG_FATAL("RENDERER FAILED TO INIT: {0}", SDL_GetError()); }
}

renderWindow::~renderWindow() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

SDL_Texture* renderWindow::loadTexture(const char* filepath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filepath);
	if (texture == NULL) { LOG_ERROR("TEXTURE FAILED TO INIT: {0}", SDL_GetError()); }
	return texture;
}

SDL_Texture* renderWindow::createTexture(int w, int h, SDL_Color c)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, 0,0,0,0);
	SDL_Rect rect;
	rect.w = w;
	rect.h = h;
	
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, c.r, c.b, c.g,c.a));
	if (surface == NULL) { LOG_ERROR("SURFACE FAILED TO INIT: {0}", SDL_GetError()); }
	texture = SDL_CreateTextureFromSurface(renderer,surface);
	if (texture == NULL) { LOG_ERROR("TEXTURE FAILED TO INIT: {0}", SDL_GetError()); }
	SDL_FreeSurface(surface);
	return texture;
}

void renderWindow::clear() { SDL_RenderClear(renderer); }

void renderWindow::fill(Uint8 r, Uint8 g, Uint8 b,Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void renderWindow::fill(SDL_Texture* tex)
{
	SDL_RenderCopy(renderer, tex, NULL, NULL);
}

void renderWindow::render(Entity& e)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = e.getW();
	src.h = e.getH();

	SDL_Rect dst;
	dst.x = (int)e.getX();
	dst.y = (int)e.getY();
	dst.w = (int)(e.getW() * e.getScalar());
	dst.h = (int)(e.getH() * e.getScalar());

	SDL_RenderCopy(renderer, e.getTexture(), &src, &dst);
}

void renderWindow::render(Entity& e, float angle, SDL_Point* centre, SDL_RendererFlip flip)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = e.getW();
	src.h = e.getH();

	SDL_Rect dst;
	dst.x = (int)e.getX();
	dst.y = (int)e.getY();
	dst.w = (int)(e.getW() * e.getScalar());
	dst.h = (int)(e.getH() * e.getScalar());

	SDL_RenderCopyEx(renderer, e.getTexture(), &src, &dst, angle, centre, flip);
}

void renderWindow::display()
{
	SDL_RenderPresent(renderer);
}
