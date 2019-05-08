#pragma once
#include "Item.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <experimental/vector>
#include "Explosion.h"

using sf::Clock;
using std::vector;
using std::unique_ptr;

class Bomb : public Item
{
public:
	// c-tor
	Bomb(const Texture& texture, const Vector2f& pos, float size);
	// d-tor
	~Bomb();

	// Draws the bomb on a Panel
	void draw(RenderTexture & panel);	// The panel to draw on.

	// Returns if the explosion is created
	bool isExplosionCreated() const;

	// Returns the vector of the explosion area
	vector<unique_ptr<Explosion>> & getExplosion();

	// Returns if the bomb is finish exploding
	bool isExploded(const Texture & texture);	// The texture to set for the explosion

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

private:
	// Creates the explosion area
	void createExplosion(const Texture & texture);	// The texture to set for the explosion

	Clock m_clock;								// Clock to count time elapsed
	bool m_isExplosionCreated;					// True if the explosion is created
	bool m_isExploded;							// True if the bomb is finish exploding
	vector<unique_ptr<Explosion>> m_explosion;	// Explosion area vector
};

