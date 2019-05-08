#include "Menu.h"
#include "GameManager.h"

using sf::VideoMode;
using std::make_unique;

const string GAME_NAME = "Bomberman";	// Name of the game
const unsigned BUTTON_SIZE = 70;		// Size of each button

Menu::Menu()
{	
}

Menu::~Menu()
{
}

void Menu::open()
{
	createWindow();	// create the menu window
	m_background.setSize(Vector2f((float)m_window.getSize().x, (float)m_window.getSize().y));	// set background as the size of the window
	m_background.setTexture(&m_rm.getBackground());

	// set the play button in the middle of the screen
	m_playButton = (make_unique<Button>(m_rm, m_window.getView().getCenter(), BUTTON_SIZE, "Play"));
	// set the exit button (3 * BUTTON_SIZE) pixels under the play button
	m_exitButton = (make_unique<Button>(m_rm, Vector2f(m_playButton->getPosition().x, m_playButton->getPosition().y + (3*BUTTON_SIZE)),
		BUTTON_SIZE, "Exit"));

	while (m_window.isOpen())	// window loop
	{
		draw();
		handleEvents();
	}
}

void Menu::createWindow()
{
	m_window.create(VideoMode(), GAME_NAME, sf::Style::Fullscreen);	// create fullscreen window
}

void Menu::draw()
{
	m_window.clear();	// clear window
	
	m_window.draw(m_background);	// draw the background

	m_playButton->draw(m_window);	// draw the 2 buttons
	m_exitButton->draw(m_window);

	m_window.display();	// display window
}

void Menu::handleEvents()
{
	Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			m_window.close();
			break;
		case Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Button::Left)	// at left mouse button press
			{
				// Save the position of the mouse click:
				const Vector2f mousePos = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				
				if (m_playButton->contains(mousePos))	// if the mouse clicked the play button
				{
					m_window.close();	// close the menu window
					startGame();		// and start the game
				}
				else if (m_exitButton->contains(mousePos))	// if the mouse clicked the exit button
					m_window.close();	// close the menu window
			}
			break;
		case Event::MouseMoved:	// at mouse move
			// Save the position of the mouse:
			const Vector2f mousePos = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

			if (m_playButton->contains(mousePos))	// if mouse hover the play button
				m_playButton->highlight();		// highlight the play button
			else
				m_playButton->unhighlight();

			if (m_exitButton->contains(mousePos))	// if mouse hover the exit button
				m_exitButton->highlight();	// highlight the exit button
			else
				m_exitButton->unhighlight();

			break;
		}
	}
}

void Menu::startGame()
{
	GameManager game(m_rm);	// make a GameManager instance
	game.play();			// and start the game
}
