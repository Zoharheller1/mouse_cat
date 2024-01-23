#pragma once
#include "Location.h"
#include "io.h"


class Controller; // Forward declaration
class Enemy
{
public:

	Enemy(int rowp, int colp);
	Enemy(Location);
	void setPosition(Location pos);
	Location getPosition() const;
	void move(Direction dir);

private:
	Location mPosition;
};

