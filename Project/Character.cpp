#include "Character.h"

Character::Character(const Texture & texture, const Vector2f & pos, float size)
	: Object(texture, pos, size), m_startingPosition(pos), m_moveSpeed(0)	// use the Object's c-tor while also initializing starting position
{																			// of the charater and movespeed
}

Character::~Character()
{
}

void Character::move(float deltaTime, const RenderTexture & panel, const Vector2f & target)
{
	m_direction = setDirection(deltaTime, target);	// set direction of movement
	m_object.move(m_direction);	// move

	if (!isInBounds(panel))	// check that the new position is not out of bounds of the panel
		stop();
}

bool Character::isInBounds(const RenderTexture & panel)
{
	if (m_object.getPosition().x < 0 || m_object.getPosition().y < 0 ||			// character is out of bounds when his x or y are less
		m_object.getPosition().x >(panel.getSize().x - m_object.getSize().x) ||	// than 0, or when x or y are greater than:
		m_object.getPosition().y >(panel.getSize().y - m_object.getSize().y))	// (panel size) - (object size)
		return false;
	
	return true;
}

void Character::reset()
{
	m_isDead = false;
	m_object.setPosition(m_startingPosition);
}

void Character::stop()
{
	m_object.move(-m_direction);	// Move the character to -direction makes it "stop"
}
