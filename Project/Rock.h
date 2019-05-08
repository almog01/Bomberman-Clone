#pragma once
#include "Item.h"
#include <SFML/Graphics.hpp>

class Rock : public Item
{
public:
	// Use the Item's c-tor
	using Item::Item;
	// d-tor
	~Rock();

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

};
