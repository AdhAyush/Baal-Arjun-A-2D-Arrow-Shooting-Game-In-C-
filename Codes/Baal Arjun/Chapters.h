#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
using namespace std;
using namespace sf;


#define no_of_chapters 2

class Chapters
{
public:

	Chapters();

	int chapter_select();




protected:
	// The game will always be in one of four states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
	State state;


	// Get the screen resolution and create an SFML window
	Vector2f resolution;

	// Here is our clock for timing everything
	Clock clock;

	//Font 
	Font font;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	//Array that contains the locked and unlocked info on levels
	int unlock_level[11];

	//lock sprites and texture
	Sprite lockSprite;
	Texture lockTexture;

	//unlock sprite and textures
	Sprite unlockSprite;
	Texture unlockTexture;

	//Chapter main heading
	Text Heading;

	//levels
	Text levelUpText;



	std::stringstream levelUpStream;



	// Prepare the sound
	SoundBuffer yadaBuffer;
	Sound yada;

};