
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

class level5 :public Levels {
private:

public:
	level5() {
		textureBackground.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\grass2.jpg");
		s.setTexture(textureBackground);
	}
	~level5() {}
	
		void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override {

			enemy[0].spawn(resolution.x / 2 + 200, resolution.y / 4, 0, 100);
			enemy[1].spawn(resolution.x / 2 + 100, resolution.y / 4 * 2, 0, 100);
			enemy[2].spawn(resolution.x / 2 + 200, resolution.y / 4 * 3, 0, 100);

			enemy[3].spawn(resolution.x / 2 + 450, resolution.y / 2 - 100, 1, 100);
			enemy[4].spawn(resolution.x / 2 + 350, resolution.y / 2 + 100, 1, 100);

			enemy[5].spawn(resolution.x / 2 + 600, resolution.y / 2, 2, 100);

		}

		void setPlayerHealth(Player& player) {
			player.setMaxHealth(70);
		}


		void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime) {

			//Loop through each enemy and update them
			
			if (enemy[3].isAlive())
				enemy[3].updateVertical(elapsedTime, resolution.y, 0);
			
			if (enemy[4].isAlive())
				enemy[4].updateVertical(elapsedTime, resolution.y, 0);


			for (int i = 0; i < 6; i++) {
				updateEnemyHealthBar(enemy[i], enemyHealth[i]);
			}

		}



		void enemyShoot(Enemy* enemy, int numEnemies, int enemyCurrentArrow, Arrow* enemyArrow, Player player) {




			for (int i = 0; i < numEnemies; i++) {
				if (enemy[i].isAlive()) {

					enemy[i]++;

					if (i < 3) {
						
						if (enemy[i].lastShootGreaterThanInterval()) {

							enemyArrow[enemyCurrentArrow].setArrowspeed(300);
							shootLinear(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow);
						}
					}
					else {

						if (enemy[i].lastShootGreaterThanInterval()) {

							enemyArrow[enemyCurrentArrow].setArrowspeed(500);
							shootTowardsPlayer(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow, player);
						}

					}
				}

			}

		}



	int run()
	{
		enemy = new Enemy[6];
		enemyHealth = new RectangleShape[6];

		int temp;
		temp = Levels::run(6);
		return temp;
	}
};