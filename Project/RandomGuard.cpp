#include "RandomGuard.h"



RandomGuard::~RandomGuard()
{
}

Vector2f RandomGuard::setDirection(float deltaTime, const Vector2f & target)
{
	setRandomDirection(deltaTime);	// set a random direction
	return m_direction;
}