#include "../include/entity.h"

float Player::getSpeed()
{
	return m_speed;
}

void Player::setSpeed(float speed)
{
	m_speed = speed;
}

void Player::moveUp()
{
	setY(getY() - getSpeed());
}

void Player::moveDown()
{
	setY(getY() + getSpeed());
}

void Player::moveLeft()
{
	setX(getX() - getSpeed());
}

void Player::moveRight()
{
	setX(getX() + getSpeed());
}

void Player::jump()
{
	jumping = true;
	setY(getY() - getSpeed());
}

void Player::jump(int jumpHeight)
{
	jumping = true;
	setY(getY() - jumpHeight);
}

void Player::stopJump() 
{
	jumping = false;
}

// TODO: collidesX and collidesY need cleaning up
bool Player::collidesX(int borderSize, int w, bool restarts)
{
	bool returnVal = false;
	if (restarts == true)
	{
		LOG_INFO("TODO MAKE COLLIDES X RESTARTS");
		return returnVal;
	}
	else
	{
		if (getX() > w - borderSize - (getW() * getScalar()))
		{
			//setX(1280 - borderSize - (getW() * getScalar()));
			returnVal = true;
		}
		else if (getX() < borderSize)
		{
			//setX(borderSize+1);
			returnVal = true;
		}
	}
	return returnVal;
}

bool Player::collision(Entity& e)	// needs a bit of work
{
	for (int i = 0; i < (getW()*getScalar()); i++) 
	{
		for (int x = 0; x < (getH()*getScalar()); x++) 
		{
			if (e.getX() == (getX() + i) and e.getY() == (getY() + x))
				return true;
		}
	}
	return false;
}

bool Player::collision(Entity& e, int w, int h)
{
	for (int i = 0; i < w; i++)
	{
		for (int x = 0; x < h; x++)
		{
			if (e.getX() == (getX() + i) and e.getY() == (getY() + x))
				return true;
		}
	}
	return false;
}

void Player::follow(Player& e, short xOffset, short yOffset,bool reversedX,bool reversedY)
{
	if (reversedX == false and reversedY == false) 
	{
		e.setY(getY() + yOffset);
		e.setX(getX() + xOffset);
	}
	else if (reversedX == true and reversedY == false) 
	{
		e.setY(getY() + yOffset);
		e.setX(getX() - xOffset);
	}
	else if (reversedX == false and reversedY == true)
	{
		e.setY(getY() - yOffset);
		e.setX(getX() + xOffset);
	}
	else if (reversedX == true and reversedY == true)
	{
		e.setY(getY() - yOffset);
		e.setX(getX() - xOffset);
	}

}

void Player::gravity()
{
	setY(getY() + getSpeed());
}

void Player::gravity(float speed)
{
	if (!jumping)
		setY(getY() + speed);
}