
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

class level2 :public Levels {
private:


public:
	level2() {
		textureBackground.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\grass.png");
		s.setTexture(textureBackground);

	}

	~level2() {}


		void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override {


			enemy[0].spawn(resolution.x / 2 + 300, resolution.y/ 2, 4, 100);

		}


		void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime)
		{
			if (enemy[0].isAlive())
				enemy[0].updateVerticalandRotate(elapsedTime, resolution.y, 0);


		}

		void setPlayerHealth(Player& player) {
			player.setMaxHealth(100);
		}



/*
		void enemyShoot(Enemy* enemy, int numEnemies, int enemyCurrentArrow, Arrow* enemyArrow, Player player)
		{
			
		}
*/

		//level 2



	int run()
	{
		enemy = new Enemy[1];
		enemyHealth = new RectangleShape[1];

		int temp;
		temp = Levels::run(1);
		return temp;
	}
};