#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <Windows.h>
#include "Player.h"
#include "Arrow.h"
#include "Enemy.h"
#include <vector>
#include "Sudarshan.h"
#include <SFML/Audio.hpp>

using namespace sf;

class Levels {
protected:

	// The game will always be in one of four states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING , WON };
	State state;


	// Get the screen resolution and create an SFML window

	Vector2f resolution;



	// Here is our clock for timing everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	IntRect arena;

	// The boundaries limits of the player
	IntRect playerArena;

	//texture of the loading screen
	sf::Texture load;
	Font font1;

	// Create the background
	VertexArray background;

	// Load the texture for our background vertex array
	Texture textureBackground;

	Texture gameOver;
	Texture youWin;

	Sprite sGameOver;
	Sprite sYouWin;



	// 100 arrow should do
	Arrow arrow[100];
	int currentArrow = 0;
	int arrowSpare = 60;
	int arrowInQuiver = 30;         // initial number of arrow in quiver
	int quiverSize = 30;            //size of the quiver to hold the arrow
	float fireRate = 2;

	// 5 sudarshans should do
	Sudarshan sudarshan[100];
	int currentSudarshan = 0;
	int SudarshanSpare = 2;
	int SudarshanInQuiver = 1;         // initial number of arrow in quiver
	int SquiverSize = 1;            //size of the quiver to hold the arrow
	float SfireRate = 2;




	// When was the fire button last pressed?
	Time lastPressed;

	// arrow shoot by enemy
	Arrow enemyArrow[100];
	int enemyCurrentArrow = 0;

	int numEnemies = 1;

	//Enemy objects Firstly one for testing
	//    Enemy enemy[numEnemies];							in each level's class



	// Load the font
	Font font;

	// Score
	Text scoreText;


	//Arrows
	Text totalArrowsText;

	//Sudarshan
	Text totalSudarshanText;

	// sprite for the background
	sf::Sprite s;

	// Health bar
	RectangleShape healthBar;

	//health bar outline
	RectangleShape outline;

	std::stringstream gameOverString;
	std::stringstream gameWonString;

	Text gameOverText;
	Text gameWonText;
	Text blankText;


	Enemy* enemy;
	RectangleShape* enemyHealth;

//	std::vector<Enemy> enemy;
//	std::vector<RectangleShape> enemyHealth;

	int tick = 0;


	// for sounds
	SoundBuffer spinBuffer;
	Sound spin;

	//war intro variable
	SoundBuffer warIntroBuffer;
	Sound warIntro;

	//player getting hit variable
	SoundBuffer playerHit;
	Sound hit;

	//fire arrow shot variable
	SoundBuffer arrowShotBuffer;
	Sound fireArrow;

	//arrow reload variable
	SoundBuffer arrowReloadBuffer;
	Sound arrowReload;


public:
	Levels();

	virtual ~Levels() {}
	int run(int num);

	virtual void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution);
	virtual void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime);
	virtual void enemyShoot(Enemy* enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow, Player player);
	virtual int run() = 0;
	virtual void setPlayerHealth(Player& p) = 0;
};