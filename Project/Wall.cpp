#include "Wall.h"
#include "Player.h"
#include "Guard.h"

Wall::~Wall()
{
}

void Wall::handleCollision(Object & obj)
{
	obj.handleCollision(*this);
}

void Wall::handleCollision(Player & player)
{
	player.handleCollision(*this);
}

void Wall::handleCollision(Guard & guard)
{
	guard.handleCollision(*this);
}

void Wall::handleCollision(Door & door)
{
}

void Wall::handleCollision(Bomb & bomb)
{
}

void Wall::handleCollision(Explosion & explosion)
{
}

void Wall::handleCollision(Rock & rock)
{
}

void Wall::handleCollision(Present & present)
{
}

void Wall::handleCollision(Wall & wall)
{
}

