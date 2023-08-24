
#include <SFML/Graphics.hpp>
#include <sstream>
#include <Windows.h>
#include "Player.h"
#include "Arrow.h"
#include "Enemy.h"
#include "level1.cpp"
#include "level2.cpp"
#include "level3.cpp"
#include "Levels.h"
#include "Chapters.h"
using namespace std;
#include <iostream>
using namespace sf;

int main()
{
	// The game will always be in one of four states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

	// Start with the GAME_OVER state
	State state = State::LEVELING_UP;

	// Get the screen resolution and create an SFML window

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Menu Screen", Style::Fullscreen);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));


	// Here is our clock for timing everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2i mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;
	

	//menuscreen
	Sprite Menu;
	//Menu.setSize(Vector2f(resolution.x, resolution.y));
	Texture textureMenu;
	textureMenu.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\arjun2.jpg");
	Menu.setTexture(textureMenu);

	float scaleX = static_cast<float>(window.getSize().x) / textureMenu.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / textureMenu.getSize().y;

	//Set the smooth property of the texture to avoid pixelation
	textureMenu.setSmooth(true);
	Menu.setScale(scaleX, scaleY);

	//font 
	Font font;
	font.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\fonts\\times.ttf");



	//play and quit coordiantes
	Vector2i play_x(1050, 1270);
	Vector2i play_y(425, 470);

	Vector2i quit_x(1050, 1270);
	Vector2i quit_y(495, 541);


	// SOUNDS

	// Prepare the sound
	SoundBuffer soundBuffer;
	soundBuffer.loadFromFile("sounds/sankh.mp3");
	Sound openingSound;
	openingSound.setBuffer(soundBuffer);

	//play the sounds
	openingSound.setVolume(50);
	openingSound.setLoop(true);
	openingSound.play();


	// The main game loop
	while (window.isOpen())
	{


		/*
		************
		Handle input
		************
		*/

		// Handle events
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
				}

				// Restart while paused
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}

				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}

			}

			// End event polling
		}


		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
			return 0;
		}


		// Handle the levelling up state
		if (state == State::LEVELING_UP)
		{

			//code for opening chapters screen for play button 

			if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{

					std::cout << event.mouseButton.x << " " << event.mouseButton.y<<endl;
					if ((play_x.x <= event.mouseButton.x) && (event.mouseButton.x <= play_x.y) && ((play_y.x <= event.mouseButton.y) && (event.mouseButton.y <= play_y.y)))
					{
						//window.close();
						int cs;
						Chapters c;
						openingSound.stop();
						cs = c.chapter_select();
						openingSound.play();

					}
				}
			}//endif

			//code for escaping the game through quit button 

			if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if ((quit_x.x <= event.mouseButton.x) && (event.mouseButton.x <= quit_x.y) && ((quit_y.x <= event.mouseButton.y) && (event.mouseButton.y <= quit_y.y)))
					{
						window.close();
						return 0;
					}
				}
			}//endif

			if (event.key.code == Keyboard::Num1) // modify this code to look for level selected i..e.  (if level ==1 ) => body remains same
			{
				//window.close();
				int cs;
				Chapters c;
				cs = c.chapter_select();
			}



			window.clear();
			window.setView(mainView);
			window.draw(Menu);
			window.display();
		}

	}
	return 0;
}