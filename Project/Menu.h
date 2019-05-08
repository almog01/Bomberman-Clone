#pragma once
#include <SFML/Graphics.hpp>
#include <experimental/vector>
#include <memory>
#include "ResourceManager.h"
#include "Button.h"

using sf::RenderWindow;
using sf::RectangleShape;
using std::unique_ptr;
using std::vector;

class Menu
{
public:
	// c-tor
	Menu();
	// d-tor
	~Menu();

	// Opens the menu window
	void open();

private:
	// Creates the menu window
	void createWindow();

	// Draws the menu
	void draw();

	// Handles the menu events
	void handleEvents();

	// Starts the Bomberman game
	void startGame();
	
	RenderWindow m_window;				// Window instance
	ResourceManager m_rm;				// Resource manager to load the needed files
	RectangleShape m_background;		// Background image of the menu
	unique_ptr<Button> m_playButton;	// Play button
	unique_ptr<Button> m_exitButton;	// Exit button
};

