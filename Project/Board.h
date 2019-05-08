#pragma once
#include <SFML/Graphics.hpp>
#include <experimental/vector>
#include <memory>
#include "Panel.h"
#include "Tile.h"

class GameManager;

using std::vector;
using std::unique_ptr;
using sf::RectangleShape;

class Board : public Panel
{
public:
	// Use the panel's c-tor
	using Panel::Panel;
	// d-tor
	~Board();

	// Set the board's size and texture
	void loadBoard(const Texture& texture);	// Texture for the board

	// Draw the board on the panel
	virtual void draw() override;

	// Returns the board panel (so we can draw objects from outside on it)
	RenderTexture & getPanel();

private:
	RectangleShape m_board;	// The board shape
};

