#include "Rock.h"
#include "Player.h"
#include "Guard.h"

Rock::~Rock()
{
}

void Rock::handleCollision(Object & obj)
{
	obj.handleCollision(*this);
}

void Rock::handleCollision(Player & player)
{
	player.handleCollision(*this);
}

void Rock::handleCollision(Guard & guard)
{
	guard.handleCollision(*this);
}

void Rock::handleCollision(Door & door)
{
}

void Rock::handleCollision(Bomb & bomb)
{
}

void Rock::handleCollision(Explosion & explosion)
{
	m_isDead = true;	// destroy the rock when collding with explosion
}

void Rock::handleCollision(Rock & rock)
{
}

void Rock::handleCollision(Present & present)
{
}

void Rock::handleCollision(Wall & wall)
{
}

