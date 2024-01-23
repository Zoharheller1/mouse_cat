#include "Enemy.h"
#include <conio.h>
#include <cstdlib>

Enemy::Enemy(int rowp, int colp) : mPosition(rowp, colp) {}

Enemy::Enemy(Location a) :mPosition(a) {}

void Enemy::setPosition(Location pos)
{
	mPosition = pos;
}

Location Enemy::getPosition()const
{
	return mPosition;
}

void Enemy::move(Direction dir) {

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
