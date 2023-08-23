
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

class level7 :public Levels {
private:

public:
	level7() {
		textureBackground.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\ice.png");
		s.setTexture(textureBackground);
	}

	~level7() {}

	void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override {

		enemy[0].spawn(resolution.x / 2 + 200, resolution.y / 6, 0, 100);
		enemy[1].spawn(resolution.x / 2 + 150, resolution.y / 6 * 2, 0, 100);
		enemy[2].spawn(resolution.x / 2 + 100, resolution.y / 6 * 3, 0, 100);
		enemy[3].spawn(resolution.x / 2 + 150, resolution.y / 6 * 4, 0, 100);
		enemy[4].spawn(resolution.x / 2 + 200, resolution.y / 6 * 5, 0, 100);
		
		enemy[5].spawn(resolution.x / 2 + 300, resolution.y / 4 * 1, 1, 100);
		enemy[6].spawn(resolution.x / 2 + 200, resolution.y / 4 * 2, 1, 100);
		enemy[7].spawn(resolution.x / 2 + 300, resolution.y / 4 * 3, 1, 100);

		enemy[8].spawn(resolution.x / 2 + 500, resolution.y / 4, 2, 100);
		enemy[9].spawn(resolution.x / 2 + 500, resolution.y / 4 * 3, 2, 100);

	}


	void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime) {


		for (int i = 0; i < 5; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);
		}

		for (int i = 4; i < 8; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			enemy[i].updateLinear(elapsedTime,800);
			//no need to check the if enemy is alive or not because this enemy can't move in this level
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);
		}

		if (enemy[8].isAlive())
			enemy[8].updateVertical(elapsedTime, resolution.y/2, 0);
		if(enemy[9].isAlive())
			enemy[9].updateVertical(elapsedTime, resolution.y, resolution.y / 2);


		for (int i = 8; i < 10; i++) {
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);
		}


	}


	void enemyShoot(Enemy* enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow, Player player) {

		for (int i = 0; i < 5; i++) {
			if (enemy[i].isAlive()) {
				enemy[i]++;
				if (enemy[i].lastShootGreaterThanInterval()) {
	
					enemyArrow[enemyCurrentArrow].setArrowspeed(300);
					shootLinear(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow);
				}
			}
		}

		for (int i = 5; i < 10; i++) {

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
		enemy = new Enemy[10];
		enemyHealth = new RectangleShape[10];

		int temp;
		temp = Levels::run(10);
		return temp;
	}
};