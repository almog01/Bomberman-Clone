#pragma once
#include "Guard.h"
#include <SFML/Graphics.hpp>

class RandomGuard : public Guard
{
public:
	// Use the Guard's c-tor
	using Guard::Guard;
	// d-tor
	~RandomGuard();

private:
	// Sets a random direction for the guard
	virtual Vector2f setDirection(float deltaTime, const Vector2f & target) override;
};

