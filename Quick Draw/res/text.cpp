#include "../include/text.h"

renderText::renderText(renderWindow& window,const char* fontpath, int fontSize, const char* messageText, SDL_Color& colour)
{
	tex = loadFont(window,fontpath,fontSize,messageText,colour);
	SDL_QueryTexture(tex, nullptr, nullptr, &textRect.w, &textRect.h);
}

void renderText::display(renderWindow& window, int x, int y)
{
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(window.renderer, tex, nullptr,&textRect);
}

SDL_Texture* renderText::loadFont(renderWindow& window,const char* fontpath, int fontSize, const char* messageText, SDL_Color& colour) 
{
	TTF_Font* font = TTF_OpenFont(fontpath, fontSize);
	if (!font) 
		LOG_FATAL("FAILED TO LOAD FONT \n");

	SDL_Surface* textSurface = TTF_RenderText_Solid(font,messageText,colour);
	if (!textSurface)
		LOG_FATAL("FAILED TO CREATE TEXT SURFACE \n");

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(window.renderer, textSurface);
	if (!textTexture) 
		LOG_FATAL("FAILED TO CREATE TEXT TEXTURE \n");
	
	TTF_CloseFont(font);
	SDL_FreeSurface(textSurface);
	return textTexture;
}

void renderText::cleanup()
{
	SDL_DestroyTexture(tex);
}
