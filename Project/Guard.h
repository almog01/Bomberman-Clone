#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>

using sf::Clock;

class Guard : public Character
{
public:
	// c-tor
	Guard(const Texture& texture, const Vector2f& pos, float size);
	// d-tor
	virtual ~Guard();

	// Collision handler for each kind of object that exist in the game (for Double Dispatch)
	virtual void handleCollision(Object & obj) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(Guard & guard) override;
	virtual void handleCollision(Door & door) override;
	virtual void handleCollision(Bomb & bomb) override;
	virtual void handleCollision(Explosion & explosion) override;
	virtual void handleCollision(Rock & rock) override;
	virtual void handleCollision(Present & present) override;
	virtual void handleCollision(Wall & wall) override;

protected:
	// Generates a random direction every constant time for the guard's movement
	void setRandomDirection(float deltaTime);	// Delta time per frame

private:
	Clock m_clock;	// Clock to count seconds between generating directions
};

