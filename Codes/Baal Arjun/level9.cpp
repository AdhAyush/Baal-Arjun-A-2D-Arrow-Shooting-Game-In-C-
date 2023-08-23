
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

class level9 :public Levels {
private:

public:
	level9() {
		textureBackground.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\sand.png");
		s.setTexture(textureBackground);
	}

	~level9() {}

	void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override {

		enemy[0].spawn(resolution.x / 2 + 200, resolution.y / 7, 0, 100);
		enemy[1].spawn(resolution.x / 2 + 170, resolution.y / 7 * 2, 0, 100);
		enemy[2].spawn(resolution.x / 2 + 150, resolution.y / 7 * 3, 0, 100);
		enemy[3].spawn(resolution.x / 2 + 150, resolution.y / 7 * 4, 0, 100);
		enemy[4].spawn(resolution.x / 2 + 170, resolution.y / 7 * 5, 0, 100);
		enemy[5].spawn(resolution.x / 2 + 200, resolution.y / 7 * 6, 0, 100);
		
		enemy[6].spawn(resolution.x / 2 + 220, resolution.y / 6 * 1, 0, 100);
		enemy[7].spawn(resolution.x / 2 + 200, resolution.y / 6 * 2, 0, 100);
		enemy[8].spawn(resolution.x / 2 + 180, resolution.y / 6 * 3, 0, 100);
		enemy[9].spawn(resolution.x / 2 + 200, resolution.y / 6 * 4, 0, 100);
		enemy[10].spawn(resolution.x / 2 + 220, resolution.y / 6 * 5, 0, 100);

		enemy[11].spawn(resolution.x / 2 + 250, resolution.y / 5 * 1, 1, 100);
		enemy[12].spawn(resolution.x / 2 + 250, resolution.y / 5 * 2, 1, 100);
		enemy[13].spawn(resolution.x / 2 + 250, resolution.y / 5 * 3, 1, 100);
		enemy[14].spawn(resolution.x / 2 + 250, resolution.y / 5 * 4, 1, 100);

		enemy[15].spawn(resolution.x / 2 + 330, resolution.y / 4 * 1, 2, 100);
		enemy[16].spawn(resolution.x / 2 + 330, resolution.y / 4 * 2, 2, 100);
		enemy[17].spawn(resolution.x / 2 + 330, resolution.y / 4 * 3, 2, 100);
	}


	void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime) {


		for (int i = 0; i < 11; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}

			enemy[i].updateLinear(elapsedTime, 500);
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);

		}

		for (int i = 11; i < 15; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			enemy[i].updateLinear(elapsedTime, 600);
			//no need to check the if enemy is alive or not because this enemy can't move in this level
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);
		}

		if(enemy[15].isAlive())
			enemy[15].updateVertical(elapsedTime, resolution.y / 2 - 50, 0);
		
		if(enemy[16].isAlive())
			enemy[17].updateVertical(elapsedTime, resolution.y , resolution.y / 2 + 50);


		for (int i = 15; i < 18; i++) {
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);
		}


	}


	void enemyShoot(Enemy* enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow, Player player) {

		for (int i = 0; i < 11; i++) {
			if (enemy[i].isAlive()) {

				enemy[i]++;
				if (enemy[i].lastShootGreaterThanInterval()) {

					enemyArrow[enemyCurrentArrow].setArrowspeed(300);
					shootLinear(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow);
				}
			}
		}

		for (int i = 11; i < 18; i++) {


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
		enemy = new Enemy[18];
		enemyHealth = new RectangleShape[18];

		int temp;
		temp = Levels::run(18);
		return temp;
	}
};