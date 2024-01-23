#include "Player.h"
#include <conio.h>
#include <cstdlib>
#include"Controller.h"

Player::Player(int rowp, int colp): mPosition(rowp,colp), mLife(3), mPoints(0){}
                         
Player::Player(Location a) :mPosition(a), mLife(3),mPoints(0){}


Player& Player::setPosition(Location place)
{
	mPosition.row = place.row;
	mPosition.col = place.col;
	return *this;
}
void Player::move(Direction dir)
{
	switch (dir)
	{
	case UP:
		mPosition.row--;
 		break;
	case DOWN:
		mPosition.row++;
		break;
	case LEFT:
		mPosition.col--;
		break;
	case RIGHT:
		mPosition.col++;
		break;
	default:
		break;
	}
}

// decreaseLife
Player& Player::decriseLife()
{
	if (mLife > 0)
	{
		mLife--;
	}
	 return *this;
}

unsigned int Player:: getPoint() const
{
	return mPoints;
}

unsigned int Player::getLife() const
{
	return mLife;
}
Location Player::getPosition() const
{
	return mPosition;
}

bool Player::isCollision(Location other)
{
	return this->mPosition.row == other.row && this->mPosition.col == other.col;
}

bool Player::isDead()
{
	return this->mLife == 0;
	// (*this).X is like this->X
	
}

/*
void Player::handleCollision(Controller& controller )
{	

	{
		
		

	}
}
*/

Player& Player::updatePoints(const char& current_place)
{
	switch (current_place)
	{
	case '*':
		mPoints += 10;
		return *this;

	case '$':
		mPoints += 5;
		return *this;
	
		
	case 'D':
		mPoints += 5;
		return *this;

	};
}