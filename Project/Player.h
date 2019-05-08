#pragma once
#include "Character.h"
#include "Bomb.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <experimental/vector>

using std::vector;
using std::unique_ptr;

class Player : public Character
{
public:
	// c-tor
	Player(const Texture& texture, const Vector2f& pos, float size);
	~Player();

	// Sets a new starting position (for using each new level)
	void setStartingPosition(const Vector2f& pos);	// The position to set
	
	// Returns the position of the player object
	Vector2f getPosition() const;

	// Returns amount of lifes left
	int getLife() const;

	// Sets the bombs count
	void setBombsCount(int amount);	// Amount to set
	// Returns amount of bombs left
	int getBombsCount() const;

	// Placeing a bomb at the player's position
	void placeBomb(const Texture& texture,			// Texture for the new bomb
				vector<unique_ptr<Bomb>>& bombs);	// Reference to vector of bombs to add the new bomb

	// Returns if the player completed the level (when colliding with door)
	bool isLevelCompleted();

	// Resets the player to his starting position while also reset level completed = false
	void reset();

	// Decrease life by 1
	void decreaseLife();

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
	// Sets the player direction based on the user input and delta timer per frame
	virtual Vector2f setDirection(float deltaTime, const Vector2f & target) override;

	int m_life;				// Amount of life left
	int m_bombsCount;		// Amount of bombs left
	bool m_levelCompleted;	// Boolean if the player completed the current level
};

