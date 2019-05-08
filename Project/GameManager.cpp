#include "GameManager.h"
#include "SmartGuard.h"
#include "RandomGuard.h"
#include "Door.h"
#include "Rock.h"
#include "Wall.h"
#include "Explosion.h"
#include "Present.h"
#include <iostream>

using sf::Keyboard;
using sf::VideoMode;
using std::cerr;
using std::make_unique;

// Enum for each objects by their character representation.
enum Char_t
{
	C_EMPTY = ' ', C_ROBOT = '/', C_WALL = '#', C_GUARD = '!', C_DOOR = 'D', C_ROCK = '@', C_PRESENT = '+', C_ROCK_N_PRESENT = '&'
};

const unsigned DATABAR_HEIGHT = 60;		// the height of the Databar
const float TILE_SIZE = 40.f;			// the size of each tile (walls, rocks, presents...)
const int MESSAGE_SIZE = 70;			// messages text size
const int MESSAGE_OUTLINE = 4;			// messages outline thickness
const string GAME_NAME = "Bomberman";	// game title
const int SCORE_PER_GUARD = 5;			// score per killing guard = (5 * number of guards at the start of the game)
const int SCORE_PER_LEVEL = 20;			// score per level completed = (20 * number of guards at the start of the game)
const int CHARACTER_PADDING = 8;		// to make the characters (player and guards) a bit smaller so they can pass freely between objects
const int INFINITY_SIGN = -1;			// -1 read from the file means infinty time or infinty bomb count 

GameManager::GameManager(ResourceManager & rm)
	: m_rm(rm), m_file(rm.getFile())
{
}

GameManager::~GameManager()
{
}

void GameManager::play()
{
	createWindow();	// create the main window

	while (loadLevel())	// keep loading levels from file untill there are no more levels
	{
		while (m_window.isOpen())	// main window loop
		{
			// each iteration:
			updateDataBar();	// update databar
			draw();				// clear, draw and display: main window, databar and board
			handleEvents();		// handles each events
			moveCharacters();	// move player and guards
			handleCollisions();	// handle collision of each object in the game
			handleDeaths();		// handle deaths of each object in the game

			if (m_player->isLevelCompleted())	// when the player reached the door
			{
				printMessage("Level Completed!");	// print message
				m_dataBar.addScore(SCORE_PER_LEVEL * m_levelGuardsCount);	// add score: (20 * number of guards at the start of the level)
				m_dataBar.increaseLevel();	// update databar level
				break;
			}
		}
	}
	printMessage("You Win!");	// if we reached here, there are no more levels to read from the file
}

bool GameManager::loadLevel()
{
	clearObjects();	// clears all the object at the start of each level

	int rows, cols;
	m_file >> rows >> cols >> m_levelTimer >> m_levelBombsCount;	// read from file: rows, cols, level timer and level bombs count

	if (m_file.eof())	// if we got to the end of file there are not any more levels
		return false;

	// initialize the board after we know the number of rows and cols. the position of the board will be under the databar (0, DATABAR_HEIGHT)
	m_board.create(Vector2f(0.f, DATABAR_HEIGHT), (cols * (unsigned)TILE_SIZE), (rows * (unsigned)TILE_SIZE));
	m_board.loadBoard(m_rm.getTile());

	m_dataBar.setTimer((float)m_levelTimer).setBombsCount(m_levelBombsCount);	// update databar with timer and bombs count

	loadObjects(rows, cols);	// read each char from the file and make the game objects
	
	m_levelGuardsCount = (unsigned)m_guards.size();	// after all objects loaded we need to remember how many guards there are in the current level

	return true;
}

void GameManager::clearObjects()
{
	m_items.clear();		// clear items vector
	m_guards.clear();		// clear guards vector
	m_bombs.clear();		// clear bombs vector
}

void GameManager::createWindow()
{
	m_window.create(VideoMode(), GAME_NAME, sf::Style::Fullscreen);	// create fullscreen window

	m_dataBar.create({ 0, 0 }, m_window.getSize().x, DATABAR_HEIGHT);	// create the databar based on the created window size
	m_dataBar.loadDataBar(TILE_SIZE, m_rm);	// load databar textures
}

void GameManager::loadObjects(unsigned rows, unsigned cols)
{
	m_file.get();		// workaround to throw away '\n'
	for (unsigned i = 0; i < rows; i++)
	{
		string line;
		getline(m_file, line);	// read each line
		for (unsigned j = 0; j < cols; j++)
		{
			Char_t c = (Char_t)line[j];	// break the line into characters
			const Vector2f currPos = Vector2f((float)j * TILE_SIZE, (float)i * TILE_SIZE);	// for each (i, j) mark the position of the object
			switch (c)
			{
			case C_ROBOT:
				if (!m_player)	// if the player is not created yet
				{	// make a new player object:
					m_player = (make_unique<Player>(m_rm.getPlayer(), currPos, TILE_SIZE - CHARACTER_PADDING));	// make player object
					m_player->setBombsCount(m_levelBombsCount);	// initial the player with bombs
				}
				else	// if the player is already created
				{
					m_player->setStartingPosition(currPos);	// just set a new starting position
					m_player->reset();						// and reset the player
					m_player->setBombsCount(m_levelBombsCount);	// set the new bombs count
				}
				break;
			case C_WALL:
				m_items.push_back(make_unique<Wall>(m_rm.getWall(), currPos, TILE_SIZE));	// make wall object
				break;
			case C_GUARD:
				addGuard(m_rm.getGuard(), currPos, TILE_SIZE - CHARACTER_PADDING);	// make random guard object (smart or random guard)
				break;
			case C_DOOR:
				m_items.push_back(make_unique<Door>(m_rm.getDoor(), currPos, TILE_SIZE));	// make door object
				break;
			case C_ROCK:
				m_items.push_back(make_unique<Rock>(m_rm.getRock(), currPos, TILE_SIZE));	// make rock object
				break;
			case C_PRESENT:
				m_items.push_back(make_unique<Present>(m_rm.getPresent(), currPos, TILE_SIZE));	// make present object
				break;
			case C_ROCK_N_PRESENT:	// make present and rock objects in the same position
				// We make the present 4 pixels smaller so it will be "hidden" under the rock
				m_items.push_back(make_unique<Present>(m_rm.getPresent(), Vector2f(currPos.x + 2 , currPos.y + 2 ), TILE_SIZE - 4));
				m_items.push_back(make_unique<Rock>(m_rm.getRock(), currPos, TILE_SIZE));
				break;
			default:
				break;
			}
		}
	}
}

void GameManager::addGuard(const Texture & texture, const Vector2f & pos, float size)
{
	unsigned randGuardType = rand() % 2;	// generate a random number: 0 or 1
	if (randGuardType == 0)	// if generated 0 - create smart guard
		m_guards.push_back(make_unique<SmartGuard>(texture, pos, size));
	else					// if generated 1 - create random guard
		m_guards.push_back(make_unique<RandomGuard>(texture, pos, size));
}

void GameManager::updateDataBar()
{
	// check the number of seconds left for the current level from the databar. if the timer is -1 there is infinity time
	if (m_dataBar.getTimer() <= 0 && m_dataBar.getTimer() != INFINITY_SIGN)
	{
		printMessage("Time's Up!");	// when the level timer is <= 0 print message
		resetLevel();				// and reset the level
	}
	m_dataBar.setLife(m_player->getLife());				// update the databar with life
	m_dataBar.setBombsCount(m_player->getBombsCount());	// and bombs count of the player
}

void GameManager::draw()
{
	m_window.clear(Color::White);	// clear the main window

	// clear and draw the databar on the main window
	m_dataBar.clear();
	m_dataBar.draw();
	m_dataBar.display(m_window);

	// clear and draw the board on the main window
	m_board.clear();
	m_board.draw();
	for (auto& item : m_items)			// draw items on the board
		item->draw(m_board.getPanel());
	for (auto& bomb : m_bombs)			// draw bombs on the board
		bomb->draw(m_board.getPanel());
	m_player->draw(m_board.getPanel());	// draw the player on the board
	for (auto& guard : m_guards)
		guard->draw(m_board.getPanel());// draw guards on the board
	m_board.display(m_window);

	m_window.display();	// display the main window after all has been drawn
}

void GameManager::moveCharacters()
{
	float dt = m_gameClock.restart().asSeconds();	// delta time per frame

	m_player->move(dt, m_board.getPanel(), { 0,0 });	// move the player based on the delta timer per frame
	for (auto& guard : m_guards)
		guard->move(dt, m_board.getPanel(), m_player->getPosition());	// move the guards based on the delta timer per frame
}

void GameManager::handleEvents()
{
	Event event;
	while (m_window.pollEvent(event))	// poll event loop
	{
		switch (event.type)
		{
		case Event::Closed:		// event of windows closed
			m_window.close();
			break;
		case Event::KeyReleased:	// event of key released
			keyReleasedHandler(event);
			break;
		}
	}
}

void GameManager::keyReleasedHandler(const Event & event)
{
	switch (event.key.code)
	{
	case Keyboard::B:	// if B button pressed
		m_player->placeBomb(m_rm.getBomb(), m_bombs);	// call the place bomb function of the player
		m_dataBar.decreaseBombsCount();	// update databar that a bomb has been placed
		break;
	case Keyboard::Space:	// if Space button pressed
		resetLevel();	// reset level
		break;
	case Keyboard::Escape:	// if Escape button pressed
		m_window.close();	// close the game
		break;
	}
}

void GameManager::handleCollisions()
{
	for (auto& item : m_items)
	{
		// Collision of items <-> player
		if (item->getGlobalBounds().intersects(m_player->getGlobalBounds()))
			item->handleCollision(*m_player);

		// Collision of guards <-> items
		for (auto& guard : m_guards)
			if (guard->getGlobalBounds().intersects(item->getGlobalBounds()))
				item->handleCollision(*guard);

		// Collision of explosion <-> rocks
		Rock* rockPtr = dynamic_cast<Rock*>(item.get());	// we only want to check collision of explosion with rocks
		if (rockPtr)										// to save runtime (there are alot of items in the game)
			for (auto& bomb : m_bombs)						// because only rocks can explode
				if (bomb->isExplosionCreated())
				{	// if the bomb is exploded
					vector<unique_ptr<Explosion>>& explosions = bomb->getExplosion();	// get the explosion area
					for (auto& explosion : explosions)
						if (explosion->getGlobalBounds().intersects(rockPtr->getGlobalBounds()))
							explosion->handleCollision(*rockPtr);
				}
	}

	for (auto& guard : m_guards)
	{
		// Collision of guards <-> player
		if (guard->getGlobalBounds().intersects(m_player->getGlobalBounds()))
			guard->handleCollision(*m_player);

		for (auto& bomb : m_bombs)
		{
			// Collision of bomb <-> guards (the bomb itself and not the bomb's explosion)
			if (bomb->getGlobalBounds().intersects(guard->getGlobalBounds()))
				bomb->handleCollision(*guard);

			// Collision of explosion <-> guards
			if (bomb->isExplosionCreated())
			{	// if the bomb is exploded
				vector<unique_ptr<Explosion>>& explosions = bomb->getExplosion();	// get the explosion area
				for (auto& explosion : explosions)
					if (explosion->getGlobalBounds().intersects(guard->getGlobalBounds()))
						explosion->handleCollision(*guard);
			}
		}
	}

	// Collision of explosion <-> player
	for (auto& bomb : m_bombs)
		if (bomb->isExplosionCreated())
		{	// if the bomb is exploded
			vector<unique_ptr<Explosion>>& explosions = bomb->getExplosion();	// get the explosion area
			for (auto& explosion : explosions)
				if (explosion->getGlobalBounds().intersects(m_player->getGlobalBounds()))
					explosion->handleCollision(*m_player);
		}
}

void GameManager::handleDeaths()
{
	for (auto bomb = m_bombs.begin(); bomb != m_bombs.end(); )
	{
		if ((*bomb)->isExploded(m_rm.getExplosion()))	// if the bomb is exploded
			bomb = m_bombs.erase(bomb);					// remove the bomb from the vector
		else
			bomb++;
	}

	for (auto item = m_items.begin(); item != m_items.end(); )
	{
		if ((*item)->isDead())			// if a rock is exploded or a present is picked up
			item = m_items.erase(item);	// remove the rock/present from the vector
		else
			item++;
	}

	for (auto guard = m_guards.begin(); guard != m_guards.end(); )
	{
		if ((*guard)->isDead())				// if a guard is dead (by explosion)
		{
			guard = m_guards.erase(guard);	// remove the guard from the vector
			m_dataBar.addScore(SCORE_PER_GUARD * m_levelGuardsCount);	// add score: (5 * number of guard at the start of the level)
		}
		else
			guard++;
	}

	if (m_player->isDead())	// if the player is dead (by guard or explosion)
		resetLevel();		// reset level
}

void GameManager::resetLevel()
{
	m_player->reset();			// return the player to his starting position
	m_player->decreaseLife();	// and decrease 1 life
	m_player->setBombsCount(m_levelBombsCount);	// reset bombs count to default
	if (m_player->getLife() == 0)	// if the player is out of life
	{
		printMessage("You Lost!");	// print message
		m_window.close();			// and end the game
		return;
	}
	printMessage("Try Again!");	// if the player still has life print "Try Again" message

	for (auto& guard : m_guards)	// reset each guard to his starting position
		guard->reset();

	m_bombs.clear();	// clear the bombs vector

	// update the databar with the new life count, boms count and timer
	m_dataBar.setLife(m_player->getLife()).setTimer(m_levelTimer).setBombsCount(m_levelBombsCount);

	m_gameClock.restart();	// restart the game clock
}

void GameManager::printMessage(string msg)
{
	msg.append("\nPress Enter To Continue...");	// append the message with "Press Enter To Continue"

	Text message(msg, m_rm.getFont(), MESSAGE_SIZE);	// make new Text instance and set it to the given string, font and size
	message.setPosition(m_window.getView().getCenter());// put the message at the middle of the window
	message.setOutlineColor(Color::Black);				// set outline color = black
	message.setOutlineThickness(MESSAGE_OUTLINE);		// set outline thickness
	message.setOrigin(message.getGlobalBounds().width / 2, message.getGlobalBounds().height / 2);	// set text origin to the center

	m_window.draw(message);	// draw the message to the window
	m_window.display();		// and display

	Event event;
	while (m_window.waitEvent(event))	// pause the game untill the player hit enter or escape
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::Enter)
				break;
			if (event.key.code == Keyboard::Escape)
			{
				m_window.close();
				break;
			}
		}
}