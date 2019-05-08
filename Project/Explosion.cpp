#include "Explosion.h"
#include "Player.h"
#include "Guard.h"
#include "Rock.h"

Explosion::~Explosion()
{
}

void Explosion::handleCollision(Object & obj)
{
	obj.handleCollision(*this);
}

void Explosion::handleCollision(Player & player)
{
	player.handleCollision(*this);
}

void Explosion::handleCollision(Guard & guard)
{
	guard.handleCollision(*this);
}

void Explosion::handleCollision(Door & door)
{
}

void Explosion::handleCollision(Bomb & bomb)
{
}

void Explosion::handleCollision(Explosion & explosion)
{
}

void Explosion::handleCollision(Rock & rock)
{
	rock.handleCollision(*this);
}

void Explosion::handleCollision(Present & present)
{
}

void Explosion::handleCollision(Wall & wall)
{
}

