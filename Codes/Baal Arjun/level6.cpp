
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

class level6 :public Levels {
private:

public:
	level6() {
		textureBackground.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\bush.png");
		s.setTexture(textureBackground);
	}

	~level6() {}

	void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override {

		enemy[0].spawn(resolution.x / 2 + 200, resolution.y / 5 , 0, 100);
		enemy[1].spawn(resolution.x / 2 + 100, resolution.y / 5 * 2, 0, 100);
		enemy[2].spawn(resolution.x / 2 + 100, resolution.y / 5 * 3, 0, 100);
		enemy[3].spawn(resolution.x / 2 + 200, resolution.y / 5 * 4, 0, 100);

		enemy[4].spawn(resolution.x / 2 + 400, resolution.y / 4 * 1, 1, 200);
		enemy[5].spawn(resolution.x / 2 + 300, resolution.y / 4 * 2, 1, 200);
		enemy[6].spawn(resolution.x / 2 + 400, resolution.y / 4 * 3, 1, 200);

		enemy[7].spawn(resolution.x / 2 + 500, resolution.y / 2 , 2, 150);

	}


	void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime) {
		

		for (int i = 0; i < 4; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			enemy[i].updateLinear(elapsedTime, 500);

			//this increase the time since last shoot     as in update it loops through all enemy objects, so it is written here to save time 
			enemy[i]++;
			updateEnemyHealthBar(enemy[i],enemyHealth[i]);
		}

		for (int i = 4; i < 8; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			//enemy[i].updateLinear(elapsedTime);
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);
			enemy[i]++;
		}



	}


	void enemyShoot(Enemy* enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow, Player player) {
		

		for (int i = 0; i < 4; i++) {
			if (enemy[i].isAlive()) {
				enemy[i]++;
				if (enemy[i].lastShootGreaterThanInterval()) {

					enemyArrow[enemyCurrentArrow].setArrowspeed(300);
					shootLinear(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow);
				}
			}
		}

		for (int i = 4; i < 8; i++) {

			if (enemy[i].isAlive()) {
				enemy[i]++;
				if (enemy[i].lastShootGreaterThanInterval()) {

					enemyArrow[enemyCurrentArrow].setArrowspeed(500);
					shootTowardsPlayer(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow, player);
				}
			}
		}
		
	}


	int run()
	{
		enemy = new Enemy[8];
		enemyHealth = new RectangleShape[8];

		int temp;
		temp = Levels::run(8);
		return temp;
	}
};