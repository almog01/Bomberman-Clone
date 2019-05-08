#pragma once
#include <SFML/Graphics.hpp>
#include <experimental/vector>
#include <fstream>

using std::ifstream;
using std::vector;
using std::string;
using sf::Texture;
using sf::Font;

class ResourceManager
{
public:
	// c-tor
	ResourceManager();
	// d-tor
	~ResourceManager();
	
	// Returns a loaded file
	ifstream & getFile();

	// Returns a loaded font
	const Font & getFont() const;

	// Getter for each loaded texture:
	const Texture & getBackground() const;	// Background texture
	const Texture & getButton() const;		// Button texture
	const Texture & getPlayer() const;		// Player texture
	const Texture & getGuard() const;		// Guard texture
	const Texture & getWall() const;		// Wall texture
	const Texture & getRock() const;		// Rock texture
	const Texture & getDoor() const;		// Door texture
	const Texture & getTile() const;		// Tile texture
	const Texture & getBomb() const;		// Bomb texture
	const Texture & getExplosion() const;	// Explosion texture
	const Texture & getPresent() const;		// Present texture
	const Texture & getHeart() const;		// Heart texture
	const Texture & getClock() const;		// Clock texture
	const Texture & getInfinity() const;	// Infinity sign texture

private:
	// Opens a file for reading. Prints error message if the open failed
	void openFile(string fileName);	// Name of the file

	// Loads all the resources needed for the game (text file, textures and font)
	void loadResources();

	// Loads a texture. Prints error message if the loading failed
	void loadTexture(Texture & texture,	// The texture to load
					string path);		// The texture file path

	// Loads a font. Prints error message if the loading failed
	void loadFont(Font & font,	// The font to load
				string path);	// The font file path

	ifstream m_file;			// File for reading.
	vector<Texture> m_textures;	// Vector to save the loaded textures.
	Font m_font;				// Game text font.
};

