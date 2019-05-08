#include "Button.h"

const unsigned TEXT_PADDING = 20;	// the padding between the button and the text inside the button

Button::Button(const ResourceManager & rm, const Vector2f & pos, unsigned btnSize, string text)
{
	// Initialize button with:
	m_button.setTexture(&rm.getButton());	// texture
	m_button.setRadius((float)btnSize);		// size
	m_button.setPosition(pos);				// position
	m_button.setOrigin(m_button.getGlobalBounds().width / 2, m_button.getGlobalBounds().height / 2);	// set origin to the middle

	// Initialize button's text with:
	m_text.setString(text);								// string
	m_text.setFont(rm.getFont());						// font
	m_text.setCharacterSize(btnSize - TEXT_PADDING);	// text_size = button_size - padding (to make the text "inside" the button)
	m_text.setFillColor(sf::Color::Red);				// color = red
	m_text.setPosition(m_button.getPosition());			// same position as the button
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().width / 2);	// set origin to the middle
}

Button::~Button()
{
}

void Button::draw(RenderWindow & window)
{
	window.draw(m_button);	// draw button
	window.draw(m_text);	// draw button's text
}

Vector2f Button::getPosition() const
{
	return m_button.getPosition();
}

bool Button::contains(const Vector2f & pos) const
{
	return m_button.getGlobalBounds().contains(pos);
}

void Button::highlight()
{
	m_button.setFillColor(sf::Color::Green);	// dye the button green to give the illusion of highlight
}

void Button::unhighlight()
{
	m_button.setFillColor(sf::Color::White);	// set color back to default
}
