#include "Present.h"
#include "Player.h"

Present::~Present()
{
}

void Present::handleCollision(Object & obj)
{
	obj.handleCollision(*this);
}

void Present::handleCollision(Player & player)
{
	m_isDead = true;	// destroy the present when the player picks it up
	player.handleCollision(*this);
}

void Present::handleCollision(Guard & guard)
{
}

void Present::handleCollision(Door & door)
{
}

void Present::handleCollision(Bomb & bomb)
{
}

void Present::handleCollision(Explosion & explosion)
{
}

void Present::handleCollision(Rock & rock)
{
}

void Present::handleCollision(Present & present)
{
}

void Present::handleCollision(Wall & wall)
{
}

