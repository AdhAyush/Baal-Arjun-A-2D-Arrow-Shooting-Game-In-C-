
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

class level3 :public Levels {
private:

public:
	level3() {
		textureBackground.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\grass2.jpg");
		s.setTexture(textureBackground);
	}

	~level3() {}


		void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override {

			enemy[0].spawn(resolution.x / 2 + 500, resolution.y/3, 5, 1);
			enemy[1].spawn(resolution.x / 2 + 200, resolution.y/3*2, 5, 1);

		}




		void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime)
		{
			if (enemy[0].isAlive())
			{
			
				enemy[0].updateVerticalandRotate(elapsedTime, resolution.y, 0);
				updateEnemyHealthBar(enemy[0], enemyHealth[0]);
			}
			if (enemy[1].isAlive())
			{
				updateEnemyHealthBar(enemy[1], enemyHealth[1]);
				enemy[1].updateVerticalandRotate(elapsedTime, resolution.y, 0);
			}
			
		}

		void setPlayerHealth(Player& player) {
			player.setMaxHealth(100);
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

						if (enemy[i].lastShootGreaterThanInterval())
						{
							enemyArrow[enemyCurrentArrow].setArrowspeed(500);
							shootTowardsPlayer(enemy[i], numEnemies, enemyCurrentArrow, enemyArrow, player);
						}
					
					}
				}

			}


		}


	int run()
	{	
		enemy = new Enemy[2];
		enemyHealth = new RectangleShape[2];
		
		int temp;
		temp = Levels::run(2);
		return temp;
	}
};