#pragma once
#include <SFML/Graphics.hpp>

using sf::Color;
using sf::Sprite;
using sf::RenderWindow;
using sf::RenderTexture;
using sf::Texture;
using sf::Vector2f;

class Panel
{
public:
	// c-tor
	Panel();
	// d-tor
	virtual ~Panel();

	// Creates a panel to the given position, with the given width and height
	void create(const Vector2f & pos,	// Position for the panel
				unsigned width,			// Panel width
				unsigned height);		// Panel height

	// Clears the panel
	void clear();

	// Draws the objects inside the panel
	virtual void draw() = 0;

	// Draws the panel on a window and displays it
	void display(RenderWindow & window); // The window to draw on.

protected:
	RenderTexture m_panel;	// The panel is built from a render texture

private:
	Sprite m_panelSprite;	// In order to draw the panel on a window, it needs a sprite
};

