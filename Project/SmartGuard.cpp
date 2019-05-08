#include "SmartGuard.h"

const float CHASE_DISTANCE = 105.f;

SmartGuard::SmartGuard(const Texture & texture, const Vector2f & pos, float size)
// use the c-tor of character, while also initializing isChasing = false
	: Guard(texture, pos, size), m_isChasing(false)
{
}

SmartGuard::~SmartGuard()
{
}


Vector2f SmartGuard::setDirection(float deltaTime, const Vector2f & target)
{
	float xDistance = target.x - m_object.getPosition().x;	// the distance difference between the guard and the player on the X axis
	float yDistance = target.y - m_object.getPosition().y;	// the distance difference between the guard and the player on the Y axis
	float distance = calcDistance(xDistance, yDistance);	// total distance

	if (distance <= CHASE_DISTANCE)	// make the guard start chasing if the player is close enougth
		m_isChasing = true;
	else
		m_isChasing = false;

	if (m_isChasing)
	{
		if (xDistance >= 0)	// Configure X axis
			m_direction.x = m_moveSpeed * deltaTime;	// Right
		else
			m_direction.x = -m_moveSpeed * deltaTime;	// Left

		if (yDistance >= 0)	// Configure Y axis
			m_direction.y = m_moveSpeed * deltaTime;	// Down
		else
			m_direction.y = -m_moveSpeed * deltaTime;	// Up
	}
	else
		setRandomDirection(deltaTime);	// if the player is far, move in a random direction
			
	return m_direction;
}

float SmartGuard::calcDistance(float x, float y)
{
	return sqrt((x*x) + (y*y));	// Pythagorean theorem
}
