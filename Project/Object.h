#pragma once
#include <SFML/Graphics.hpp>

class Player;
class Guard;
class Door;
class Bomb;
class Explosion;
class Rock;
class Present;
class Wall;

using sf::RenderTexture;
using sf::RectangleShape;
using sf::FloatRect;
using sf::Vector2f;
using sf::Texture;

class Object
{
public:
	// c-tor
	Object(const Texture& texture,	// Object's texture
			const Vector2f& pos,	// Object's position
			float size);			// Object's size
	// d-tor
	virtual ~Object();

	// Draws the object on a panel
	void draw(RenderTexture & panel);	// The panel to draw on.

	// Returns the bounding rectangle that blocks the object (global bounds)
	FloatRect getGlobalBounds() const;
	
	// Returns if the object is dead or not
	bool isDead() const;

	// Collision handler for each kind of object that exist in the game (for Double Dispatch)
	virtual void handleCollision(Object & obj) = 0;
	virtual void handleCollision(Player & player) = 0;
	virtual void handleCollision(Guard & guard) = 0;
	virtual void handleCollision(Door & door) = 0;
	virtual void handleCollision(Bomb & Bomb) = 0;
	virtual void handleCollision(Explosion & explosion) = 0;
	virtual void handleCollision(Rock & rock) = 0;
	virtual void handleCollision(Present & present) = 0;
	virtual void handleCollision(Wall & wall) = 0;

protected:
	RectangleShape m_object;	// The object's shape
	bool m_isDead;				// Boolean that tells if the object is dead or not
};

