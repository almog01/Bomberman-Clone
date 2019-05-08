#include "Panel.h"

Panel::Panel()
{
}

Panel::~Panel()
{
}

void Panel::create(const Vector2f & pos, unsigned width, unsigned height)
{
	m_panel.create(width, height);	// create a panel with the given width and height
	m_panelSprite.setPosition(pos);	// set panel's sprite position
	m_panelSprite.setTexture(m_panel.getTexture(), true);	// set panel's sprite texture
}

void Panel::clear()
{
	m_panel.clear(Color::Cyan);	// clear the panel and set Cyan background
}

void Panel::display(RenderWindow & window)
{
	window.draw(m_panelSprite);	// draw the panel's sprite to the window
	m_panel.display();			// display
}
