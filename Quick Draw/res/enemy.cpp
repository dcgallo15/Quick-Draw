#include "../include/entity.h"

bool Enemy::eCollision(Entity& e) 
{
	bool returnVal = false;

	SDL_Rect baseRect;
	baseRect.x = (int)e.getX();
	baseRect.y = (int)e.getY();
	baseRect.w = (int)(e.getW()*e.getScalar());
	baseRect.h = (int)(e.getH()*e.getScalar());

	SDL_Rect enemyRect;
	enemyRect.x = (int)getX();
	enemyRect.y = (int)getY();
	enemyRect.w = (int)(getW()*getScalar());
	enemyRect.h = (int)(getH()*getScalar());

	if (SDL_IntersectRect(&baseRect, &enemyRect,&enemyRect))	// IntersectRect is GREAT! (work on own collision system)
	{
		returnVal = true;
	}
	return returnVal;

}