#pragma once

#include <SDL_ttf.h>
#include "renderWindow.h"
#include "log.h"

// forward declaration is needed when passing a class into a function and class is in another file
class renderWindow;

class renderText 
{
	SDL_Texture* tex = nullptr;
	SDL_Rect textRect;
public:
	renderText(renderWindow& window,const char* fontpath, int fontSize, const char* messageText, SDL_Color& colour);
	void display(renderWindow& window,int x,int y);
	SDL_Texture* loadFont(renderWindow& window,const char* fontpath, int fontSize, const char* messageText, SDL_Color& colour);


	void cleanup();
};