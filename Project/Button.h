#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

using sf::CircleShape;
using sf::Texture;
using sf::Vector2f;
using sf::RenderWindow;
using sf::Text;

class Button
{
public:
	// c-tor
	Button(const ResourceManager & rm,	// Resource manager to load button texture and text font
			const Vector2f &pos,		// Button's position
			unsigned btnSize,			// Button's size
			string text);				// The text inside the button
	// d-tor
	~Button();

	// Draws the button on a window
	void draw(RenderWindow & window); // The window to draw on

	// Returns the position of the button
	Vector2f getPosition() const;
	
	// Returns true if the button global bounds contains the given position
	bool contains(const Vector2f & pos) const;	// The given position

	// Highlights the button by dying it green
	void highlight();
	// Unhighlights the button
	void unhighlight();

private:
	CircleShape m_button;	// The button
	Text m_text;			// The text inside the button
};

