#pragma once

#include "entity.h"
#include "log.h"
#include <SDL.h>
#include <SDL_image.h>

class Entity;

class renderWindow
{
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	renderWindow(const char*,int,int);
	~renderWindow();

	SDL_Texture* loadTexture(const char* filepath);
	SDL_Texture* createTexture(int w,int h,SDL_Color c);
	void clear();
	void fill(Uint8 r, Uint8 g, Uint8 b,Uint8 a);
	void fill(SDL_Texture* tex);
	// need to add an overloaded fill that takes in a texture for the background

	void render(Entity& e);
	void render(Entity& e, float angle, SDL_Point* centre = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void display();

	friend class renderText;
};