
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Player.h"
#include "Arrow.h"
#include "Enemy.h"
#include "levels.h"
#include "Background.h"
#include "ArrowShootUpdate.h"
#include "EnemyHealthPosition.h"
#include <iostream>

using namespace sf;

class level10 :public Levels {
private:

public:
	level10() {
		textureBackground.loadFromFile("graphics/sand.png");
		s.setTexture(textureBackground);

	}

	~level10()
	{
		std::cout << "level 10 destructor" << std::endl;
	}
	void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override {


		enemy[0].spawn(resolution.x / 2 + 200, resolution.y / 7, 0, 100);
		enemy[1].spawn(resolution.x / 2 + 170, resolution.y / 7 * 2, 0, 100);
		enemy[2].spawn(resolution.x / 2 + 150, resolution.y / 7 * 3, 0, 100);
		enemy[3].spawn(resolution.x / 2 + 150, resolution.y / 7 * 4, 0, 100);
		enemy[4].spawn(resolution.x / 2 + 170, resolution.y / 7 * 5, 0, 100);
		enemy[5].spawn(resolution.x / 2 + 200, resolution.y / 7 * 6, 0, 100);

		enemy[6].spawn(resolution.x / 2 + 220, resolution.y / 6 * 1, 0, 100);
		enemy[7].spawn(resolution.x / 2 + 200, resolution.y / 6 * 2, 2, 300);
		enemy[8].spawn(resolution.x / 2 + 180, resolution.y / 6 * 3, 0, 100);
		enemy[9].spawn(resolution.x / 2 + 200, resolution.y / 6 * 4, 2, 300);
		enemy[10].spawn(resolution.x / 2 + 220, resolution.y / 6 * 5, 0, 100);

		enemy[11].spawn(resolution.x / 2 + 270, resolution.y / 5 * 1, 1, 200);
		enemy[12].spawn(resolution.x / 2 + 270, resolution.y / 5 * 2, 2, 300);
		enemy[13].spawn(resolution.x / 2 + 270, resolution.y / 5 * 3, 2, 300);
		enemy[14].spawn(resolution.x / 2 + 270, resolution.y / 5 * 4, 1, 200);
		
		enemy[15].spawn(resolution.x / 2 + 350, resolution.y / 4 * 1, 2, 300);
		enemy[16].spawn(resolution.x / 2 + 350, resolution.y / 4 * 2, 2, 300);
		enemy[17].spawn(resolution.x / 2 + 350, resolution.y / 4 * 3, 2, 300);
		
		enemy[18].spawn(resolution.x / 2 + 430, resolution.y / 5 * 1, 1, 200);
		enemy[19].spawn(resolution.x / 2 + 430, resolution.y / 5 * 2, 1, 200);
		enemy[20].spawn(resolution.x / 2 + 430, resolution.y / 5 * 3, 1, 200);
		enemy[21].spawn(resolution.x / 2 + 430, resolution.y / 5 * 4, 1, 200);
	}


	void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime) {


		for (int i = 0; i < 6; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			enemy[i].updateLinear(elapsedTime, 500);
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);

		}

		for (int i = 5; i < 11; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			enemy[i].updateLinear(elapsedTime, 600);
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);

		}

		for (int i = 11; i < 15; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			enemy[i].updateLinear(elapsedTime, 700);
			//no need to check the if enemy is alive or not because this enemy can't move in this level
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);
		}



		for (int i = 15; i < 22; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);
		}


	}


	void enemyShoot(Enemy* enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow, Player player) {

		for (int i = 0; i < 11; i++) {
			if (enemy[i].isAlive()) {
				enemy[i]++;
				if (i == 7 || i == 9) {
					if (enemy[i].lastShootGreaterThanInterval()) {

						enemyArrow[enemyCurrentArrow].setArrowspeed(500);
						shootTowardsPlayer(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow, player);
					}
					continue;
				}

				if (enemy[i].lastShootGreaterThanInterval()) {

					enemyArrow[enemyCurrentArrow].setArrowspeed(300);
					shootLinear(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow);
				}
			}
		}

		for (int i = 11; i < 22; i++) {


			if (enemy[i].isAlive()) {
				enemy[i]++;
				if (enemy[i].lastShootGreaterThanInterval()) {

					enemyArrow[enemyCurrentArrow].setArrowspeed(500);
					shootTowardsPlayer(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow, player);
				}
			}

		}

	}

	void setPlayerHealth(Player& player) {
		player.setMaxHealth(320);
	}


	int run()
	{
		enemy = new Enemy[22];
		enemyHealth = new RectangleShape[22];

		int temp;
		temp = Levels::run(22);
		return temp;
	}
};