#pragma once
#include "Location.h"
#include <io.h>


class Controller; // Forward declaration

class Player
{
public:

	Player(int rowp, int colp);
	Player(Location);

	unsigned int getPoint() const;
	unsigned int getLife() const;
	Location getPosition() const;
	
	// check if player.m_pos collides with other locstion.
	bool isCollision(Location other);

	bool isDead();
	// handle life loss, handle death
	//void handleCollision(Controllercontroller);

/*

	Option2:

	handleCollision will get Controller* and then does this:

	checkCollision(Cont* controller)
	{
		m_life--;
		if(m_life <= 0 )
			controller->resetGame()

	}
*/
	
	Player& updatePoints(const char &);
	Player& setPosition(Location place);
	void move(Direction dir);
	Player& decriseLife();
private:

	Location mPosition; 
	unsigned int mLife;
	unsigned int mPoints;
	
};
