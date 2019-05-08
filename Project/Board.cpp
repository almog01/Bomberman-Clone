#include "Board.h"
#include "GameManager.h"

using sf::Vector2f;
using std::make_unique;

Board::~Board()
{
}

void Board::loadBoard(const Texture& texture)
{
	m_board.setSize({ (float)m_panel.getSize().x, (float)m_panel.getSize().y });	// set the board's size same as the panel size
	m_board.setTexture(&texture);	// set board texture
}

void Board::draw()
{
	m_panel.draw(m_board);	// draw the board Rectangle Shape on the panel
}

RenderTexture & Board::getPanel()
{
	return m_panel;
}
