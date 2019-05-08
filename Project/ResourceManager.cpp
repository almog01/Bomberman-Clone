#include "ResourceManager.h"
#include <Windows.h>

// Enum for the loaded textures positions. 
enum Texture_t
{
	T_BACKGROUND, T_BUTTON, T_ROBOT, T_GUARD, T_WALL, T_ROCK, T_DOOR, 
	T_TILE, T_BOMB, T_EXPLOSION, T_PRESENT, T_HEART, T_CLOCK, T_INFINITY
};

const size_t NUM_OF_TEXTURES = 14;			// number of textures that need to be loaded
const string FILE_NAME = "board.bomb.txt";	// the text file name


ResourceManager::ResourceManager()
{
	loadResources();
}

ResourceManager::~ResourceManager()
{
}

ifstream & ResourceManager::getFile()
{
	return m_file;
}

const Texture & ResourceManager::getBackground() const
{
	return m_textures[T_BACKGROUND];
}

const Texture & ResourceManager::getButton() const
{
	return m_textures[T_BUTTON];
}

const Texture & ResourceManager::getPlayer() const
{
	return m_textures[T_ROBOT];
}

const Texture & ResourceManager::getGuard() const
{
	return m_textures[T_GUARD];
}

const Texture & ResourceManager::getWall() const
{
	return m_textures[T_WALL];
}

const Texture & ResourceManager::getRock() const
{
	return m_textures[T_ROCK];
}

const Texture & ResourceManager::getDoor() const
{
	return m_textures[T_DOOR];
}

const Texture & ResourceManager::getTile() const
{
	return m_textures[T_TILE];
}

const Texture & ResourceManager::getBomb() const
{
	return m_textures[T_BOMB];
}

const Texture & ResourceManager::getExplosion() const
{
	return m_textures[T_EXPLOSION];
}

const Texture & ResourceManager::getPresent() const
{
	return m_textures[T_PRESENT];
}

const Texture & ResourceManager::getHeart() const
{
	return m_textures[T_HEART];
}

const Texture & ResourceManager::getClock() const
{
	return m_textures[T_CLOCK];
}

const Texture & ResourceManager::getInfinity() const
{
	return m_textures[T_INFINITY];
}

const Font & ResourceManager::getFont() const
{
	return m_font;
}

void ResourceManager::loadResources()
{
	openFile(FILE_NAME);	// open the text file

	m_textures.resize(NUM_OF_TEXTURES);	// resize the texture vector
	// load each texture to his position in the vector:
	loadTexture(m_textures[T_BACKGROUND], "res/img/background.png");
	loadTexture(m_textures[T_BUTTON], "res/img/button.png");
	loadTexture(m_textures[T_ROBOT], "res/img/robot.png");
	loadTexture(m_textures[T_GUARD], "res/img/guard.png");
	loadTexture(m_textures[T_WALL], "res/img/wall.png");
	loadTexture(m_textures[T_ROCK], "res/img/rock.png");
	loadTexture(m_textures[T_DOOR], "res/img/door.jpg");
	loadTexture(m_textures[T_TILE], "res/img/tile.png");
	m_textures[T_TILE].setRepeated(true);	// the tile texture is used as background for the board so he needs to be repeated
	loadTexture(m_textures[T_BOMB], "res/img/bomb.png");
	loadTexture(m_textures[T_EXPLOSION], "res/img/explosion.png");
	loadTexture(m_textures[T_PRESENT], "res/img/present.png");
	loadTexture(m_textures[T_HEART], "res/img/heart.png");
	loadTexture(m_textures[T_CLOCK], "res/img/clock.png");
	loadTexture(m_textures[T_INFINITY], "res/img/infinity.png");

	loadFont(m_font, "res/font/chary.ttf");	// load the font file
}

void ResourceManager::openFile(string fileName)
{
	m_file.open(fileName);
	if (!m_file.is_open())	// if file doesn't exist
	{
		MessageBoxA(NULL, "File doesn't exist", "Error", MB_OK | MB_ICONEXCLAMATION);	// print error message
		exit(EXIT_FAILURE);
	}
}

void ResourceManager::loadTexture(Texture & texture, string path)
{
	if (!texture.loadFromFile(path))	// if texture couldn't be loaded
	{
		MessageBoxA(NULL, "Error loading texture!", "Error", MB_OK | MB_ICONEXCLAMATION);	// print error message
		exit(EXIT_FAILURE);
	}
}

void ResourceManager::loadFont(Font & font, string path)
{
	if (!font.loadFromFile(path))	// if font couldn't be loaded
	{
		MessageBoxA(NULL, "Error loading font!", "Error", MB_OK | MB_ICONEXCLAMATION);	// print error message
		exit(EXIT_FAILURE);
	}
}
