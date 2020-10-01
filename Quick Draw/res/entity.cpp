#include "../include/entity.h"

Entity::Entity(SDL_Texture* tex,float x, float y, int w, int h, float scalar)
	:m_tex(tex),m_y(y), m_x(x),m_w(w),m_h(h),m_scalar(scalar)
{
}

void Entity::cleanUp() 
{
	SDL_DestroyTexture(m_tex);
}

float Entity::getX()
{
	return m_x;
}

float Entity::getY()
{
	return m_y;
}

void Entity::setX(float x) 
{
	m_x = x;
}

void Entity::setY(float y) 
{
	m_y = y;
}

int Entity::getW()
{
	return m_w;
}

int Entity::getH()
{
	return m_h;
}

float Entity::getScalar()
{
	return m_scalar;
}

void Entity::setScalar(float scalar) 
{
	m_scalar = scalar;
}

SDL_Texture* Entity::getTexture() 
{
	return m_tex;
}

void Entity::setTexture(SDL_Texture*& tex)
{
	m_tex = tex;
}
