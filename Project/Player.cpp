#include "Player.h"

using sf::Keyboard;
using std::make_unique;

const int STARTING_LIFE = 3;	// start the player with 3 lifes
const int INFINITY_SIGN = -1;	// -1 means infinty bomb count 
const float MOVE_SPEED = 120.f;	// player's movespeed

Player::Player(const Texture & texture, const Vector2f & pos, float size)
// use the c-tor of character, while also initializing life, bombs count, level completed = false, and movespeed
	: Character(texture, pos, size), m_life(STARTING_LIFE), m_bombsCount(0), m_levelCompleted(false)
{
	m_moveSpeed = MOVE_SPEED;
}

Player::~Player()
{
}

void Player::setStartingPosition(const Vector2f& pos)
{
	m_startingPosition = pos;	// set the new starting position
	m_object.setPosition(pos);	// and also move the object
}

Vector2f Player::getPosition() const
{
	return m_object.getPosition();	// return position
}

int Player::getLife() const
{
	return m_life;	// return life
}

void Player::setBombsCount(int amount)
{
	m_bombsCount = amount;	// set bomb count
}

int Player::getBombsCount() const
{
	return m_bombsCount;	// return bombs count
}

void Player::placeBomb(const Texture & texture, vector<unique_ptr<Bomb>>& bombs)
{
	if (m_bombsCount > 0 || m_bombsCount == INFINITY_SIGN)	// check that placing bomb is possible
	{
		// If there is already a bomb on the player position we don't want to place another one
		for (auto& bomb : bombs)
			if (m_object.getGlobalBounds().intersects(bomb->getGlobalBounds()))
				return;

		// place the bomb on the same position of the player and the same size
		bombs.push_back(make_unique<Bomb>(texture, m_object.getPosition(), m_object.getSize().x));
		
		if (m_bombsCount != INFINITY_SIGN)	// if there is limit for bombs
			m_bombsCount--;					// decrease 1 bomb
	}
}

bool Player::isLevelCompleted()
{
	return m_levelCompleted;	// return if level completed
}

void Player::reset()
{
	m_levelCompleted = false;	// set level completed = false
	Character::reset();			// use the character's reset function
}

void Player::decreaseLife()
{
	m_life--;	// decrease life by 1
}

Vector2f Player::setDirection(float deltaTime, const Vector2f & target)
{
	// multiply each direction by (movespeed * deltaTime) for a constant movement between computers with different frame per second
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		return { 0, -m_moveSpeed * deltaTime };		// up = {0, -y}
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		return { 0, m_moveSpeed * deltaTime };		// down = {0, y}	
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		return { -m_moveSpeed * deltaTime, 0 };		// left = {-x, 0}
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		return { m_moveSpeed * deltaTime, 0 };		// right = {x, 0}
	}
	return { 0,0 };
}

void Player::handleCollision(Object & obj)
{
	obj.handleCollision(*this);
}

void Player::handleCollision(Player & player)
{
}

void Player::handleCollision(Guard & guard)
{
	m_isDead = true;	// die when colliding with guard
}

void Player::handleCollision(Door & door)
{
	m_levelCompleted = true;	// colliding with door = level complete
}

void Player::handleCollision(Bomb & bomb)
{
}

void Player::handleCollision(Explosion & explosion)
{
	m_isDead = true;	// die when colliding with explosion
}

void Player::handleCollision(Rock & rock)
{
	stop();	// stop movement when colliding with rock
}

void Player::handleCollision(Present & present)
{
	if (m_bombsCount != INFINITY_SIGN)	// if there is a limit for bombs count
		m_bombsCount++;					// add bomb when colliding with present
}

void Player::handleCollision(Wall & wall)
{
	stop();	// stop movement when colliding with wall
}
