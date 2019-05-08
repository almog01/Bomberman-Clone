#pragma once
#include "Guard.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class SmartGuard : public Guard
{
public:
	// c-tor
	SmartGuard(const Texture& texture, const Vector2f& pos, float size);
	// d-tor
	~SmartGuard();

private:
	// Sets the direction of the guard to chase the player if he's close enougth
	virtual Vector2f setDirection(float deltaTime, const Vector2f & target) override;

	// Calculate distance using Pythagorean theorem
	float calcDistance(float x, float y);

	bool m_isChasing;	// True if the guard is chasing the player
};

