#include "Bomb.h"
#include "Guard.h"

using std::make_unique;

const float TIME_TO_EXPLODE = 4.f;		// the time from the moment the player placed the bomb until it explodes
const float TIME_OF_EXPLOSION = 1.5f;	// the time from the moment the bomb expldes until it disapear

Bomb::Bomb(const Texture & texture, const Vector2f & pos, float size)
// use the c-tor of character, while also initializing isExploded = false and isExplosionCreated = false
	: Item(texture, pos, size), m_isExploded(false), m_isExplosionCreated(false)
{
}

Bomb::~Bomb()
{
}

void Bomb::draw(RenderTexture & panel)
{
	if (!m_isExplosionCreated)		// if the bomb isn't exploding, draw the bomb itself
		Item::draw(panel);
	else					// if the bomb is exploding, draw the explosion
		for (auto& explosion : m_explosion)
			explosion->draw(panel);
}

bool Bomb::isExplosionCreated() const
{
	return m_isExplosionCreated;	// return if the explosion is created
}

vector<unique_ptr<Explosion>>& Bomb::getExplosion()
{
	return m_explosion;	// return explosion vector
}

bool Bomb::isExploded(const Texture & texture)
{
	float timeElapsed = m_clock.getElapsedTime().asSeconds();	// time elapsed of the clock

	if (!m_isExplosionCreated && timeElapsed >= TIME_TO_EXPLODE)	// if the explosion is not created yet and 4 seconds elapsed
	{
		createExplosion(texture);	// create explosion
		m_isExplosionCreated = true;
		m_clock.restart();			// restart clock
	}
	else if (m_isExplosionCreated && timeElapsed >= TIME_OF_EXPLOSION)	// if the explosion is created and 1.5 seconds elapsed
		m_isExploded = true;	// set that the bomb is exploded

	return m_isExploded;
}

void Bomb::handleCollision(Object & obj)
{
	obj.handleCollision(*this);
}

void Bomb::handleCollision(Player & player)
{
}

void Bomb::handleCollision(Guard & guard)
{
	guard.handleCollision(*this);
}

void Bomb::handleCollision(Door & door)
{
}

void Bomb::handleCollision(Bomb & bomb)
{
}

void Bomb::handleCollision(Explosion & explosion)
{
}

void Bomb::handleCollision(Rock & rock)
{
}

void Bomb::handleCollision(Present & present)
{
}

void Bomb::handleCollision(Wall & wall)
{
}

void Bomb::createExplosion(const Texture & texture)
{
	// Bomb's explosion area is his own cell, and the four adjacent cells: up, down, left and right.
	// get each cell position:
	const Vector2f currPos = { m_object.getPosition().x, m_object.getPosition().y };
	const Vector2f up = { m_object.getPosition().x, m_object.getPosition().y - m_object.getSize().y };
	const Vector2f down = { m_object.getPosition().x, m_object.getPosition().y + m_object.getSize().y };
	const Vector2f left = { m_object.getPosition().x - m_object.getSize().x, m_object.getPosition().y };
	const Vector2f right = { m_object.getPosition().x + m_object.getSize().x, m_object.getPosition().y };
	// make explosion object for each cell:
	m_explosion.push_back(make_unique<Explosion>(texture, currPos, m_object.getSize().x));
	m_explosion.push_back(make_unique<Explosion>(texture, up, m_object.getSize().x));
	m_explosion.push_back(make_unique<Explosion>(texture, down, m_object.getSize().x));
	m_explosion.push_back(make_unique<Explosion>(texture, left, m_object.getSize().x));
	m_explosion.push_back(make_unique<Explosion>(texture, right, m_object.getSize().x));
}