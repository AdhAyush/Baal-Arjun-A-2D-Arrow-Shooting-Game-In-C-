
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

class level4 :public Levels {
private:
	const int numEnemies = 3;
	int numEnemiesAlive = numEnemies;

	sf::Sprite s;
	sf::Sprite s_load;

public:
	level4() {
		textureBackground.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\grass.png");
		s.setTexture(textureBackground);
	}
	~level4() {}
	void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override {

		enemy[0].spawn(resolution.x / 2 + 200, resolution.y / 4, 0, 1, 100);
		enemy[1].spawn(resolution.x / 2 + 100, resolution.y / 4 * 2, 0, 1, 100);
		enemy[2].spawn(resolution.x / 2 + 200, resolution.y / 4 * 3, 0, 1, 100);

		enemy[3].spawn(resolution.x / 2 + 400, resolution.y / 2 - 100, 1, 1, 100);
		enemy[4].spawn(resolution.x / 2 + 400, resolution.y / 2 + 100, 1, 1, 100);

		enemy[5].spawn(resolution.x / 2 + 600, resolution.y / 2, 2, 1, 100);

	}


	void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime) {

		//Loop through each enemy and update them
		enemy[5].updateVertical(elapsedTime, resolution.y, 0);

		
		for (int i = 0; i < 6; i++) {
			updateEnemyHealthBar(enemy[i], enemyHealth[i]);
		
		}
		
	}



	void enemyShoot(Enemy* enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow, Player player) {


		for (int i = 0; i < numEnemies; i++) {
			
			if (enemy[i].isAlive()) {
				enemy[i]++;

				if (i < 3) {

					if (enemy[i].lastShootGreaterThanInterval()) {
						shootLinear(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow);
					}
				}

				else {
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