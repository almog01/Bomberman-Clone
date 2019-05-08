#pragma once
#include <SFML/Graphics.hpp>
#include <experimental/vector>
#include <memory>
#include <fstream>
#include "ResourceManager.h"
#include "Item.h"
#include "Player.h"
#include "Guard.h"
#include "Bomb.h"
#include "Board.h"
#include "DataBar.h"

using std::ifstream;
using std::vector;
using std::unique_ptr;
using sf::RenderWindow;
using sf::Event;
using sf::Clock;
using std::string;

class GameManager
{
public:
	// c-tor
	GameManager(ResourceManager & rm);	// Resource manager reference for: file, font and textures
	// d-tor
	~GameManager();

	// Runs the game
	void play();

private:
	// Loads all the needed data for the level. Returns false if there are not any more levels
	bool loadLevel();

	// Clears all the object (to start a clean level)
	void clearObjects();

	// Creates a window.
	void createWindow();

	// Loads all the objects from the file
	void loadObjects(unsigned rows,	// Numbers of raws to read
					unsigned cols);	// Numbers of columns to read

	// Makes a new random guard: Smart Guard or Random Guard
	void addGuard(const Texture & texture,	// Guard texture
					const Vector2f & pos,	// Guard position
					float size);			// Guard size

	// Updates Data bar with life and bombs count
	void updateDataBar();

	// Draws the toolbar and the board on the window, and than displays it.
	void draw();

	// Call the move functions of the player and guards based on the game clock
	void moveCharacters();

	// Handles the events of the user
	void handleEvents();
	// Handles the events of any keyboard button was released
	void keyReleasedHandler(const Event & event);

	// Call the collisions of any 2 type of objects that can collide with each other (Double Dispatch)
	void handleCollisions();

	// Handles the deaths of: Bombs, rocks, presents, guards and the player
	void handleDeaths();

	// Handles all the actions needed to reset the current level
	void resetLevel();

	// Prints a message with the given string to the middle of the window, and pauses the game
	void printMessage(string msg);	// The given string to print

	RenderWindow m_window;				// Window instance.
	ResourceManager & m_rm;				// Reference to a resource manager
	ifstream & m_file;					// Reference to an opened file
	DataBar m_dataBar;					// Databar instance
	Board m_board;						// Board instance
	unique_ptr<Player> m_player;		// Player instance
	vector<unique_ptr<Guard>> m_guards;	// Vector of guard
	vector<unique_ptr<Item>> m_items;	// Vector of items
	vector<unique_ptr<Bomb>> m_bombs;	// Vector of bombs
	Clock m_gameClock;					// The main game clock
	float m_levelTimer;					// The timer to set for the current level
	int m_levelBombsCount;				// The number of bombs count to set for the current level
	unsigned m_levelGuardsCount;		// The number of guards at the start of the level
};

