#include "Door.h"
#include "Player.h"

Door::~Door()
{
}

void Door::handleCollision(Object & obj)
{
	obj.handleCollision(*this);
}

void Door::handleCollision(Player & player)
{
	player.handleCollision(*this);
}

void Door::handleCollision(Guard & guard)
{
}

void Door::handleCollision(Door & door)
{
}

void Door::handleCollision(Bomb & bomb)
{
}

void Door::handleCollision(Explosion & explosion)
{
}

void Door::handleCollision(Rock & rock)
{
}

void Door::handleCollision(Present & present)
{
}

void Door::handleCollision(Wall & wall)
{
}


