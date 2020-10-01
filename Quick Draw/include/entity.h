#pragma once

#include "log.h"
#include <SDL.h>

class Entity
{
	SDL_Texture* m_tex;
	float m_x, m_y, m_scalar;
	int m_w, m_h;

public:
	Entity(SDL_Texture* tex, float x, float y, int w, int h, float scalar = 1.0f);
	void cleanUp();

	void setX(float x);
	void setY(float y);

	int getW();
	int getH();

	float getX();
	float getY();

	float getScalar();
	void setScalar(float scalar);

	SDL_Texture* getTexture();
	void setTexture(SDL_Texture*& tex);
};

class Player : public Entity
{
	float m_speed;
	bool jumping;
public:
	using Entity::Entity;	// inherited constructor

	float getSpeed();
	void setSpeed(float speed);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void jump();
	void jump(int jumpHeight);
	void stopJump();

	bool collidesX(int borderSize,int w,bool restarts = false);
	bool collision(Entity& e);
	bool collision(Entity& e, int w, int h);

	void follow(Player& e, short xOffset, short yOffset,bool reversedX = false, bool reversedY = false);

	void gravity();
	void gravity(float speed);
};

class Enemy : public Player
{

public:
	using Player::Player;	

	bool eCollision(Entity&);
};