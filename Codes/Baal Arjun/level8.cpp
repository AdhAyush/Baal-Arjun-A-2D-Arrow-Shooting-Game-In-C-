
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

class level8 :public Levels {
private:

public:
	level8() {
		textureBackground.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\grass3.png");
		s.setTexture(textureBackground);
	}

	~level8() {}

	void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override {

		enemy[0].spawn(resolution.x / 2 + 150, resolution.y / 6, 0, 200);
		enemy[1].spawn(resolution.x / 2 + 120, resolution.y / 6 * 2, 0, 200);
		enemy[2].spawn(resolution.x / 2 + 100, resolution.y / 6 * 3, 0, 200);
		enemy[3].spawn(resolution.x / 2 + 120, resolution.y / 6 * 4, 0, 200);
		enemy[4].spawn(resolution.x / 2 + 150, resolution.y / 6 * 5, 0, 200);

		enemy[5].spawn(resolution.x / 2 + 200, resolution.y / 4 * 1, 0, 200);
		enemy[6].spawn(resolution.x / 2 + 170, resolution.y / 4 * 2 + 50, 0, 200);
		enemy[7].spawn(resolution.x / 2 + 200, resolution.y / 4 * 3, 0, 200);

		enemy[8].spawn(resolution.x / 2 + 300, resolution.y / 4, 1, 300);
		enemy[9].spawn(resolution.x / 2 + 300, resolution.y / 4 * 2, 1, 300);
		enemy[10].spawn(resolution.x / 2 + 300, resolution.y / 4 * 3, 1,300);

		enemy[11].spawn(resolution.x / 2 + 400, resolution.y / 3 * 1, 2, 300);
		enemy[12].spawn(resolution.x / 2 + 400, resolution.y / 3 * 2, 2, 300);

	}


	void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime) {


		for (int i = 0; i < 8; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			enemy[i].updateLinear(elapsedTime, 600);
			enemyHealth[i].setSize(Vector2f(enemy[i].getHealth() / enemy[i].getMaxHealth() * 20, 3));
			enemyHealth[i].setPosition(enemy[i].getCenter().x, enemy[i].getCenter().y - 10);
			enemyHealth[i].setFillColor(Color::Red);

		}

		for (int i = 8; i < 11; i++) {
			if (!enemy[i].isAlive()) {
				continue;
			}
			enemy[i].updateLinear(elapsedTime, 800);
			// 
			//no need to check the if enemy is alive or not because this enemy can't move in this level
			enemyHealth[i].setSize(Vector2f(enemy[i].getHealth() / enemy[i].getMaxHealth() * 20, 3));
			enemyHealth[i].setPosition(enemy[i].getCenter().x, enemy[i].getCenter().y - 10);
			enemyHealth[i].setFillColor(Color::Red);
		}
		if(enemy[11].isAlive())
			enemy[11].updateVertical(elapsedTime, resolution.y / 2, 0);
		
		if(enemy[12].isAlive())
			enemy[12].updateVertical(elapsedTime, resolution.y, resolution.y / 2);

		for (int i = 11; i < 13; i++) {
			enemyHealth[i].setSize(Vector2f(enemy[i].getHealth() / enemy[i].getMaxHealth() * 20, 3));
			enemyHealth[i].setPosition(enemy[i].getCenter().x, enemy[i].getCenter().y - 10);
			enemyHealth[i].setFillColor(Color::Red);
		}


	}


	void enemyShoot(Enemy* enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow, Player player) {

		for (int i = 0; i < 8; i++) {
			if (enemy[i].isAlive()) {

				enemy[i]++;
				if (enemy[i].lastShootGreaterThanInterval()) {

					enemyArrow[enemyCurrentArrow].setArrowspeed(300);
					shootLinear(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow);
				}
			}
		}

		for (int i = 8; i < 13; i++) {

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
		enemy = new Enemy[13];
		enemyHealth = new RectangleShape[13];

		int temp;
		temp = Levels::run(13);
		return temp;
	}
};