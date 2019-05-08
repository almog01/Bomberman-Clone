#pragma once
#include <SFML/Graphics.hpp>
#include "Panel.h"
#include "ResourceManager.h"

using sf::RectangleShape;
using sf::Texture;
using sf::Text;
using sf::Font;
using sf::Clock;
using sf::Color;

class DataBar : public Panel
{
public:
	// Use the panel's c-tor
	using Panel::Panel;
	// d-tor
	~DataBar();

	// Loads all the icons and texts that are going to be printed on the Data Bar
	void loadDataBar(float iconSize, const ResourceManager & rm);

	// Increase level by 1
	DataBar& increaseLevel();

	// Sets the life to the given amount
	DataBar& setLife(int amount);

	// Sets the timer to the given amount
	DataBar& setTimer(float amount);
	// Returns number of time left
	float getTimer() const;

	// Adds the given amount to the score
	DataBar& addScore(int amount);
	// Sets the score to the given amount
	DataBar& setScore(int amount);

	// Sets the bombs count to the given amount
	DataBar& setBombsCount(int amount);
	// Returns number of bombs left
	int getBombsCount() const;
	// Decrease bombs count by 1
	DataBar& decreaseBombsCount();
	
	// Draw the Data Bar on the panel
	virtual void draw() override;

private:
	// Initialize a shape with size, texture and position
	RectangleShape iniShape(const Vector2f & iconSize, const Texture & texture, const Vector2f & pos);
	
	// Initialize a text with font, size, colort and position
	Text iniText(const Font & font, unsigned characterSize, const Color & color, const Vector2f & pos);

	// Draw the level text on the panel
	void drawLevel();
	// Draw the life icons on the panel
	void drawLife();
	// Draw the clock icon and time text on the panel
	void drawTimer();
	// Draw the clock icon and time text on the panel
	void drawBombCount();
	// Draw the score text on the panel
	void drawScore();

	int m_level = 1;		// The current level
	int m_life = 0;			// Number of lifes left
	int m_score = 0;		// The score
	int m_bombsCount = 0;	// Number of bombs left
	float m_timer = 0;		// Game timer
	
	// Rectangle shape for each icon:
	RectangleShape m_heartIcon;		// Heart icon
	RectangleShape m_clockIcon;		// Clock icon
	RectangleShape m_bombIcon;		// Bomb icon
	RectangleShape m_infinityIcon;	// Infinity icon
	// Text instance for each string:
	Text m_levelTxt;	// Level text
	Text m_timerTxt;	// Timer text
	Text m_scoreTxt;	// Score text
	Text m_bombsTxt;	// Bombs left text

	Clock m_timerClock;	// Timer clock
};

