
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Player.h"
#include "Arrow.h"
#include "Enemy.h"
#include "levels.h"
#include "Background.h"
#include "ArrowShootUpdate.h"
#include "EnemyHealthPosition.h"

using namespace sf;

class level1 :public Levels {
private:
	const int numEnemies = 3;
	int numEnemiesAlive = numEnemies;
	sf::Sprite s;
	sf::Sprite s_load;

public:
	level1() {
		textureBackground.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\grass.png");
		s.setTexture(textureBackground);

		lockStatus = false;


	}
	~level1() {}

	void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override {

		if (numEnemiesAlive == 5) {
			for (int i = 0; i < numEnemiesAlive; i++) {
				if (i < 3)
					enemy[i].spawn(resolution.x / 2, resolution.y / 4 * (i + 1), 1, 1, 100);
				else
					enemy[i].spawn(resolution.x / 2 + 100, resolution.y / 6 * (i - 2), 0, 1, 100);
			}
		}
		else {
			for (int i = 0; i < numEnemiesAlive; i++) {
				if (i % 3 == 0)
					enemy[i].spawn(resolution.x / 2, resolution.y / 4, 0, 1, 100);

				else if (i % 3 == 1)
					enemy[i].spawn(resolution.x / 2, resolution.y / 2, 1, 1, 100);
				else
					enemy[i].spawn(resolution.x / 2, resolution.y / 3, 2, 1, 100);

			}
		}
	}


	void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime) {

		//Loop through each Zombie and update them
		for (int i = 0; i < numEnemies; i++)
		{

			if (i < 3 && enemy[i].isAlive() ){
				//enemy[i].update();

				updateEnemyHealthBar(enemy[i], enemyHealth[i]);
				
			}
			else {

				if (enemy[i].isAlive())
				{
				
					enemy[i].update(elapsedTime, playerPosition, resolution);
					updateEnemyHealthBar(enemy[i], enemyHealth[i]);
				}
			}
		}


	}


	void enemyShoot(Enemy* enemy, int numEnemies, int &enemyCurrentArrow, Arrow* enemyArrow, Player player) {

		for (int i = 0; i < numEnemies; i++) {
			if (enemy[i].isAlive()) {

				enemy[i]++;

				if (i < 3) {

					if (enemy[i].lastShootGreaterThanInterval()) {
						shootLinear(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow);
					}
				}
				else
				{

					if (enemy[i].lastShootGreaterThanInterval()) {
						shootTowardsPlayer(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow, player);
					}

				}
			}


		}

	}


	int run(int num)
	{
		enemy = new Enemy[num];
		enemyHealth = new RectangleShape[num];

		int temp;
		temp = Levels::run(num);
		return temp;
	}
};