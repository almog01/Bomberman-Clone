#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"

using sf::Vector2f;
using sf::RenderTexture;

class Character : public Object
{
public:
	// c-tor
	Character(const Texture& texture, const Vector2f& pos, float size);
	// d-tor
	virtual ~Character();

	// Moves the character based on delta time per frame, and checks that the character is not out of bounds
	void move(float deltaTime,				// Delta time per frame
			const RenderTexture & panel,	// The panel to check bounds
			const Vector2f & target);		// The target to chase (for SmartGuard)

	// Resets the character to his starting position
	void reset();

protected:
	// Virtual function for each derived character to choose his direction to move
	virtual Vector2f setDirection(float deltaTime, const Vector2f & target) = 0;
	
	// Stops the character from moving
	void stop();

	Vector2f m_direction;			// Direction of movement
	Vector2f m_startingPosition;	// The position of the charater at the start of the level
	float m_moveSpeed;				// Character's move speed

private:
	// Checks that the object is still in the boundaries of a panel
	bool isInBounds(const RenderTexture & panel);	// The panel to check
};

