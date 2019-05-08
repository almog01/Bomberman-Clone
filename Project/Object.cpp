#include "Object.h"

Object::Object(const Texture& texture, const Vector2f& pos, float size)
	: m_object({ size, size}), m_isDead(false)	// initialize object size and isDead = false
{
	m_object.setTexture(&texture);	// set object texture
	m_object.setPosition(pos);		// set object position
}

Object::~Object()
{
}

void Object::draw(RenderTexture & panel)
{
	panel.draw(m_object);	// draw the object on the panel
}

FloatRect Object::getGlobalBounds() const
{
	return m_object.getGlobalBounds();	// return global bounds
}

bool Object::isDead() const
{
	return m_isDead;	// return boolean isDead
}
