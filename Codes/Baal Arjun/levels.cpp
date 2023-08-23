#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Player.h"
#include "Arrow.h"
#include "Enemy.h"
#include "levels.h"
#include "Background.h"


Levels::Levels() {
	// Start with the GAME_OVER state
	state = State::LEVELING_UP;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;


	// About the game
	int score = 0;
	int hiScore = 0;

	//font load
	font.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\fonts\\times.ttf");

	//font load
	font1.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\fonts\\trial.ttf");

	//score text
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 0);

	//arrowtext
	totalArrowsText.setFont(font);
	totalArrowsText.setCharacterSize(40);
	totalArrowsText.setFillColor(Color::Red);
	totalArrowsText.setPosition(resolution.x / 20, resolution.y / 20);

	//arrowtext
	totalSudarshanText.setFont(font);
	totalSudarshanText.setCharacterSize(40);
	totalSudarshanText.setFillColor(Color::Red);
	totalSudarshanText.setPosition(resolution.x / 40, resolution.y / 20);


	//health bar
	healthBar.setSize(Vector2f(100, 10));
	healthBar.setFillColor(Color::Blue);
	healthBar.setPosition(resolution.x / 20, resolution.y / 20 + 55);

	//healthbar outline
	outline.setSize(Vector2f(100, 10));
	outline.setFillColor(Color::Transparent);
	outline.setOutlineColor(Color::Black);
	outline.setOutlineThickness(3);
	outline.setPosition(Vector2f(resolution.x / 20, resolution.y / 20 + 55));

	gameOverString << " \t\t\t\t\t\t\tYOU LOSE\n\npress enter to continue...";

	gameOverText.setFont(font1);
	gameOverText.setCharacterSize(60);
	gameOverText.setFillColor(Color::Cyan);
	gameOverText.setPosition(resolution.x / 2 - 500, resolution.y / 2- 70);



	gameWonString << "\t\t\t\t\t\t\tYOU WON\n\npress enter to continue...";

	gameWonText.setFont(font1);
	gameWonText.setCharacterSize(60);
	gameWonText.setFillColor(Color::Cyan);
	gameWonText.setPosition(resolution.x / 2-500, resolution.y / 2-70);

	gameWonText.setString(gameWonString.str());
	gameOverText.setString(gameOverString.str());


	sGameOver.setTexture(gameOver);
	sYouWin.setTexture(youWin);

	sGameOver.setPosition(resolution.x / 2, resolution.y / 2);
	sYouWin.setPosition(resolution.x / 2, resolution.y / 2);


	//sounds

	//sudarshan sound
	spinBuffer.loadFromFile("sounds/spining.wav");
	spin.setBuffer(spinBuffer);

	// war intro sound
	warIntroBuffer.loadFromFile("sounds/warIntro.mp3");
	warIntro.setBuffer(warIntroBuffer);

	// fire arrow shot
	arrowShotBuffer.loadFromFile("sounds/fireArrow.mp3");
	fireArrow.setBuffer(arrowShotBuffer);

	// player getting hit sound
	playerHit.loadFromFile("sounds/playerHit.mp3");
	hit.setBuffer(playerHit);

	// arrow reload
	arrowReloadBuffer.loadFromFile("sounds/arrowReload.mp3");
	arrowReload.setBuffer(arrowReloadBuffer);

}


void Levels::spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) {}
void Levels::update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime) {}
void Levels::enemyShoot(Enemy* enemy, int numEnemies, int &enemyCurrentArrow, Arrow* enemyArrow, Player player) {}


int Levels::run(int num)
{
	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Baal Arjun", Style::Fullscreen);
	
	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	int numEnemies = num;
	int numEnemiesAlive = numEnemies;

	// The main game loop
	while (window.isOpen())
	{


		/*
		************
		Handle input
		************
		*/

		
		// Handle event
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
					return 1;
				}

				else if (event.key.code == Keyboard::Return &&
					state == State::WON)
				{
					return 0;
				}

				if (state == State::PLAYING)
				{
					// Reloading
					if (event.key.code == Keyboard::R)
					{	
						arrowReload.play();
						//for arrow
						if (arrowSpare > 0)
						{
							// Plenty of arrow. Reload.
							int temp;
							temp = quiverSize - arrowInQuiver;
							arrowInQuiver += temp;
							arrowSpare -= temp;
						}
						else if (arrowSpare <= 0)
						{
							// Only few arrow left
							arrowInQuiver = arrowSpare;
							arrowSpare = 0;
						}
						//for sudarshan
						if (SudarshanSpare > 0)
						{
							// Plenty of arrow. Reload.
							int temp;
							temp = SquiverSize - SudarshanInQuiver;
							SudarshanInQuiver += temp;
							SudarshanSpare -= temp;
						}
						else if (SudarshanSpare <= 0)
						{
							// Only few arrow left
							SudarshanInQuiver = SudarshanSpare;
							SudarshanSpare = 0;
						}

					}

				}

			}
		}// End event polling


		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
			return 1;
		}
		
		// Handle controls while playing
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}

			// Fire a ArrowcurrentArrow
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				if (gameTimeTotal.asMilliseconds()
					- lastPressed.asMilliseconds()
						> 1000 / fireRate && arrowInQuiver > 0)
				{
					// Pass the centre of the player 
					// and the centre of the cross-hair
					// to the shoot function
					arrow[currentArrow].shoot(
						player.getCenter().x, player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y,1);

					fireArrow.play();
					currentArrow++;
					if (currentArrow > 99)
					{
						currentArrow = 0;
					}
					lastPressed = gameTimeTotal;

					arrowInQuiver--;
				}

			}// End fire a ArrowcurrentArrow

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{

				if (gameTimeTotal.asMilliseconds()
					- lastPressed.asMilliseconds()
						> 500 / SfireRate && SudarshanInQuiver > 0)
				{

					// Pass the centre of the player 
					// and the centre of the cross-hair
					// to the shoot function
					sudarshan[currentSudarshan].shootSudarshan(
						player.getCenter().x, player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);
					spin.play();
					currentSudarshan++;
					if (currentSudarshan > 99)
					{
						currentSudarshan = 0;
					}
					lastPressed = gameTimeTotal;

					SudarshanInQuiver--;
				}

			}// End fire a SudarshanArrow


		}// End WASD while playing

		// Handle the levelling up state
		if (state == State::LEVELING_UP)
		{
			
			//here state is made playing just easiness for testing purpose
			//later on above code will be uncommented and further code will be added
			state = State::PLAYING;

			//game starts here
			if (state == State::PLAYING)
			{
				warIntro.play();

				//arena of the battleground
				arena.width = resolution.x;
				arena.height = resolution.y;
				arena.left = 0;
				arena.top = 0;

				// We will modify this line of code later
				//int tileSize = 50;
				int tileSize = createBackground(background, arena);

				//restricting the space for movement of player
				playerArena.width = resolution.x /4 ;
				playerArena.height = resolution.y;
				playerArena.left = 0;
				playerArena.top = 0;

				// Spawn the player 
				player.spawn(playerArena, resolution, tileSize);

				spawn(enemy, numEnemiesAlive, resolution);
			

				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
		}// End levelling up

		/*
		****************
		UPDATE THE FRAME
		****************
		*/
		if (state == State::PLAYING)
		{
			// Update the delta time
			Time dt = clock.restart();
			// Update the total game time
			gameTimeTotal += dt;
			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(), mainView);

			// Update the player
			player.update(dtAsSeconds, Mouse::getPosition());

			// Make a note of the players new position

			Vector2f playerPosition(player.getCenter());

			//update the enemy
			update(enemy, enemyHealth, numEnemies, resolution, playerPosition, dt.asSeconds());

			//enemy shooting arrow towards the player
			enemyShoot(enemy, numEnemies, enemyCurrentArrow, enemyArrow, player);
			
			// Collision detection
			// Have any enemy been shot?
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < numEnemies; j++)
				{
					if (arrow[i].isInFlight() &&
						enemy[j].isAlive())
					{
						if (arrow[i].getPosition(1).intersects
						(enemy[j].getPosition()))
						{
							// Stop the bullet
							arrow[i].stop();

							// Register the hit and see if it was a kill
							if (enemy[j].hit()) {
								//Not just a hit but a kill too
								// score += 10;
								// if (score >= hiScore)
								// {
								//	hiScore = score;
								// }

								numEnemiesAlive--;

								// When all the enemy are dead (again)
								if (numEnemiesAlive == 0) {
									state = State::WON;
								}
							}

						}
					}

				}
			}// End enemy being shot

				//for sudarshan
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < numEnemies; j++)
				{
					if (sudarshan[i].isInFlight() && enemy[j].isAlive())
					{
						if (sudarshan[i].getPosition().intersects(enemy[j].getPosition()))
						{
							try
							{
								sudarshan[i].isInFlight();
							}
							catch (const std::out_of_range& e)
							{
								std::cout << "Sudarshan finished!/n" << e.what() << std::endl;
							}

							// Register the hit and see if it was a kill
							if (enemy[j].hit(i)) {
								//Not just a hit but a kill too
								// score += 10;
								// if (score >= hiScore)
								// {
								//	hiScore = score;
								// }

								numEnemiesAlive--;

								// When all the enemy are dead (again)
								if (numEnemiesAlive == 0) {
									state = State::WON;
								}
							}

						}
					}

				}
			}// End enemy being shot



			// checking player being shot
			for (int i = 0; i < 100; i++)
			{

				//checking all possiblities for arrows in flight
				if (enemyArrow[i].isInFlight())
				{
					//if arrow hits the player
					if (enemyArrow[i].getPosition().intersects
					(player.getPosition()))
					{
						hit.play();
						// Stop the bullet
						enemyArrow[i].stop();
						player.hit();


					}
				}
			}// End player being shot

				// Update any arrow that are in-flight
			for (int i = 0; i < 100; i++)
			{
				if (arrow[i].isInFlight())
				{
					arrow[i].update(dtAsSeconds, resolution,1);
				}

				//this is possible because number of arrow possible is same for both enemy and player
				if (enemyArrow[i].isInFlight())
				{
					enemyArrow[i].update(dtAsSeconds, resolution);

				}
			}

			// Update Sudarshan that is in-flight
			for (int i = 0; i < 100; i++)
			{
				if (sudarshan[i].isInFlight())
				{
					sudarshan[i].update(dtAsSeconds, resolution);
				}
				
			
			}


			healthBar.setSize(Vector2f(player.getHealth() / player.getMaxHealth() * 100, 10));
			healthBar.setPosition(resolution.x / 20, resolution.y / 20 + 55);


			std::stringstream aarrows;
			std::stringstream scores;

			aarrows << arrowInQuiver << " / " << arrowSpare;
			totalArrowsText.setString(aarrows.str());





		}// End updating the scene

		/*
		**************
		Draw the scene
		**************
		*/

		if (state == State::PLAYING)
		{
			window.clear();

			// set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);

			// Draw the background
			window.draw(background, &textureBackground);
		
			//Draw Blood Splash on th ground 
				
			for (int i = 0; i < numEnemies; i++) {
				if (!enemy[i].isAlive()) {
					window.draw(enemy[i].getSprite());
				}
			}


			// Draw the enemy above the ground where blood splash are present i.e enemy walk over the blood splash
			for (int i = 0; i < numEnemies; i++)
			{
				if (enemy[i].isAlive()) {
					window.draw(enemy[i].getSprite());      //check the number of enemis and varify the getsprite tomorrow
					window.draw(enemyHealth[i]);
				}
			}

			// Draw the player
			window.draw(player.getSprite());


			//Draw the arrow
			for (int i = 0; i < 100; i++)
			{
				if (arrow[i].isInFlight())
				{
					window.draw(arrow[i].getSprite(1));
				}

				if (enemyArrow[i].isInFlight())
				{
					window.draw(enemyArrow[i].getSprite());
				}
			}

			//Draw the sudarshan
			for (int i = 0; i < 100; i++)
			{
				if (sudarshan[i].isInFlight())
				{
					window.draw(sudarshan[i].getSprite());
				}

			}

			// Draw the HUD
			window.draw(totalArrowsText);

			// draw the hud for sudarshan
			window.draw(totalSudarshanText);

			// Draw the outline
			window.draw(outline);

			// Draw the health bar
			window.draw(healthBar);

			if (player.getHealth() <= 0) {
				state = State::GAME_OVER;
			}

		}

		if (state == State::GAME_OVER) {
			window.clear();

			window.draw(background, &textureBackground);
			
			window.draw(player.getSprite());

			// Draw the HUD
			window.draw(totalArrowsText);

			// Draw the outline
			window.draw(outline);

			// Draw the health bar
			window.draw(healthBar);

			

			tick++;

			if ((tick < 40)) {
				window.draw(gameOverText);
			}
			else if (tick > 80) {
				//window.draw(blankText);
				tick = 0;
			}
			else {}



		}

		if (state == State::WON) {
			window.clear();
			window.draw(background, &textureBackground);

			window.draw(player.getSprite());

			// Draw the HUD
			window.draw(totalArrowsText);

			//Draw Sudarshan
			window.draw(totalSudarshanText);

			// Draw the outline
			window.draw(outline);

			// Draw the health bar
			window.draw(healthBar);

			//  
			
			tick++;

			if ((tick < 40)) {
				window.draw(gameWonText);
			}
			else if (tick > 80) {
				//window.draw(blankText);
				tick = 0;
			}
			else {}

		}

		window.display();

	}// End game loop

	return 1;
};


