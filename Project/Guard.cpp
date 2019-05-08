#include "Guard.h"
#include "Player.h"

enum Direction_t { UP, DOWN, LEFT, RIGHT };	// Enum for each direction

const float MOVE_SPEED = 35.f;				// guard's movespeed
const unsigned DIRECTIONS = 5;				// 5 directions for movement: up, down, left, right and stay
const float DIRECTION_PER_SECOND = 1.5f;	// to generate random direction every 1.5 seconds

Guard::Guard(const Texture & texture, const Vector2f & pos, float size)
	: Character(texture, pos, size)
// use the c-tor of character, while also initializing movespeed
{
	m_moveSpeed = MOVE_SPEED;
}

Guard::~Guard()
{
}

void Guard::handleCollision(Object & obj)
{
	obj.handleCollision(*this);	// call the other object's collision
}

void Guard::handleCollision(Player & player)
{
	player.handleCollision(*this);
}

void Guard::handleCollision(Guard & guard)
{
}

void Guard::handleCollision(Door & door)
{
}

void Guard::handleCollision(Bomb & bomb)
{
	stop();	// stop movement when colliding with bomb
}

void Guard::handleCollision(Explosion & explosion)
{
	m_isDead = true;	// die when colliding with explosion
}

void Guard::handleCollision(Rock & rock)
{
	stop();	// stop movement when colliding with rock
}

void Guard::handleCollision(Present & present)
{
}

void Guard::handleCollision(Wall & wall)
{
	stop();	// stop movement when colliding with wall
}

void Guard::setRandomDirection(float deltaTime)
{
	float timeElapsed = m_clock.getElapsedTime().asSeconds();	// get the time elapsed

	if (timeElapsed >= DIRECTION_PER_SECOND)	// if time elapsed is greater than 1.5 we generate a new random direction
	{
		unsigned randDirection = rand() % DIRECTIONS;	// generate random number between 0 and 4

		// multiply each direction by (movespeed * deltaTime) for a constant movement between computers with different frame per second
		switch (randDirection)
		{
		case UP:
			m_direction = Vector2f(0, -m_moveSpeed * deltaTime);
			break;
		case DOWN:
			m_direction = Vector2f(0, m_moveSpeed * deltaTime);
			break;
		case LEFT:
			m_direction = Vector2f(-m_moveSpeed * deltaTime, 0);
			break;
		case RIGHT:
			m_direction = Vector2f(m_moveSpeed * deltaTime, 0);
			break;
		default:
			m_direction = Vector2f(0, 0);
			break;
		}
		m_clock.restart();	// restart clock after generating direction
	}
}
