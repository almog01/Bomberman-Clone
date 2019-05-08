#include "DataBar.h"

using std::to_string;

const float LEVEL_POS = 20;
const float LIFE_POS = 230;
const float CLOCK_POS = 410;
const float BOMB_POS = 580;
const float SCORE_POS = 700;
const unsigned TEXT_SIZE = 45;
const int INFINITY_SIGN = -1;

DataBar::~DataBar()
{
}

void DataBar::loadDataBar(float iconSize, const ResourceManager & rm)
{
	const float middleHeight = (float)m_panel.getSize().y / 2;	// the middle of the panel height

	// initialize the level text with font, size, color and position
	m_levelTxt = iniText(rm.getFont(), TEXT_SIZE, Color::Black, { LEVEL_POS, 0 });

	// initialize the heart icon with size, texture and position
	m_heartIcon = iniShape({ iconSize, iconSize }, rm.getHeart(), { LIFE_POS, middleHeight });

	// initialize the clock icon with size, texture and position
	m_clockIcon = iniShape({ iconSize, iconSize }, rm.getClock(), { CLOCK_POS, middleHeight });
	// initialize the timer text with font, size, color and position (position = to the right of the clock icon)
	m_timerTxt = iniText(rm.getFont(), TEXT_SIZE, Color::Black, { m_clockIcon.getPosition().x + iconSize, 0 });

	// initialize the bomb icon with size, texture and position
	m_bombIcon = iniShape({ iconSize, iconSize }, rm.getBomb(), { BOMB_POS, middleHeight });
	// initialize the bomb count text with font, size, color and position (position = to the right of the bomb icon)
	m_bombsTxt = iniText(rm.getFont(), TEXT_SIZE, Color::Black, { m_bombIcon.getPosition().x + iconSize, 0 });

	// initialize the score text with font, size, color and position
	m_scoreTxt = iniText(rm.getFont(), TEXT_SIZE, Color::Black, { SCORE_POS, 0 });

	// initialize the infinity icon with size, texture and position
	m_infinityIcon = iniShape({ iconSize, iconSize }, rm.getInfinity(), { 0, middleHeight });
}

DataBar & DataBar::increaseLevel()
{
	m_level++;	// increase level by 1
	return *this;
}

DataBar& DataBar::setLife(int amount)
{
	m_life = amount;	// set life
	return *this;
}

DataBar & DataBar::setTimer(float amount)
{
	m_timerClock.restart();	// restart the clock before assigning the new timer
	m_timer = amount;	// set timer
	return *this;
}

float DataBar::getTimer() const
{
	return m_timer;	 // return timer
}

DataBar& DataBar::addScore(int amount)
{
	m_score += amount;	// add score
	return *this;
}

DataBar& DataBar::setScore(int amount)
{
	m_score = amount;	// set score
	return *this;
}

DataBar& DataBar::setBombsCount(int amount)
{
	m_bombsCount = amount;	 // set bombs count
	return *this;
}

int DataBar::getBombsCount() const
{
	return m_bombsCount;	// return bombs count
}

DataBar& DataBar::decreaseBombsCount()
{
	m_bombsCount--;	// decrease bombs count by 1
	return *this;
}

void DataBar::draw()
{
	drawLevel();		// draw level
	drawLife();			// draw the heart icons
	drawTimer();		// draw the clock icon and timer
	drawBombCount();	// draw bombs count
	drawScore();		// draw score
}

RectangleShape DataBar::iniShape(const Vector2f & iconSize, const Texture & texture, const Vector2f & pos)
{
	RectangleShape shape(iconSize);	// create a temporary shape with the given size
	shape.setTexture(&texture);		// set shape texture
	shape.setPosition(pos);			// set shape position
	shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);	// set the shape origin to the center
	return shape;	// return the created shape
}

Text DataBar::iniText(const Font & font, unsigned characterSize, const Color & color, const Vector2f & pos)
{
	Text text;				// create a temporary text
	text.setFont(font);		// set text font
	text.setCharacterSize(characterSize);	// set text size
	text.setFillColor(color);	// set text color
	text.setPosition(pos);		// set text position
	return text;	// return the created text
}

void DataBar::drawLevel()
{
	m_levelTxt.setString("Level:" + to_string((int)m_level));	// update string
	m_panel.draw(m_levelTxt);									// draw
}

void DataBar::drawLife()
{
	for (int i = 0; i < m_life; i++)	// for each life left draw a heart icon
	{
		RectangleShape heartCopy(m_heartIcon);	// make the heart icon copy
		// set the position of each draw to the right of the last one
		heartCopy.setPosition(m_heartIcon.getPosition().x + (m_heartIcon.getSize().x * i), m_heartIcon.getPosition().y);
		m_panel.draw(heartCopy);	// draw
	}
}

void DataBar::drawTimer()
{
	m_panel.draw(m_clockIcon);	// draw clock icon
	if (m_timer == INFINITY_SIGN)	// if the timer is -1 (infinity time)
	{	// set the position of the infinity icon to the right of the clock icon
		m_infinityIcon.setPosition(m_clockIcon.getPosition().x + m_clockIcon.getSize().x, m_infinityIcon.getPosition().y);
		m_panel.draw(m_infinityIcon);	// draw infinity
	}
	else
	{
		float dt = m_timerClock.restart().asSeconds();	// delta time per frame
		m_timer -= dt;	// reduce the delta time from the timer
		m_timerTxt.setString(to_string((int)m_timer));	// update text string
		m_panel.draw(m_timerTxt);	// draw text
	}
}

void DataBar::drawBombCount()
{
	m_panel.draw(m_bombIcon);	// draw bomb icon
	if (m_bombsCount == INFINITY_SIGN)	// if the bombs count is -1 (infinity bombs)
	{	// set the position of the infinity icon to the right of the bomb icon
		m_infinityIcon.setPosition(m_bombIcon.getPosition().x + m_bombIcon.getSize().x, m_infinityIcon.getPosition().y);
		m_panel.draw(m_infinityIcon);	// draw infinity
	}
	else
	{
		m_bombsTxt.setString(to_string((int)m_bombsCount));	// update text string
		m_panel.draw(m_bombsTxt);	// draw text
	}
}

void DataBar::drawScore()
{
	m_scoreTxt.setString("Score: " + to_string((int)m_score));	// update text string
	m_panel.draw(m_scoreTxt);	// draw text
}
