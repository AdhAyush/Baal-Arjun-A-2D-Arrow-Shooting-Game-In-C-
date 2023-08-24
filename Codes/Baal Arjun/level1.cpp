
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

public:
	level1() {
		textureBackground.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\grass.png");
		s.setTexture(textureBackground);

	}
	~level1() {}

	void spawn(Enemy* enemy, int numEnemiesAlive, Vector2f resolution) override
		{

		enemy[0].spawn(2 * resolution.x / 3, resolution.y / 3, 3, 100);


	}

	void setPlayerHealth(Player& player) {
		player.setMaxHealth(100);
	}

		/* 
		void update(Enemy* enemy, RectangleShape* enemyHealth, int numEnemies, Vector2f resolution, Vector2f playerPosition, float elapsedTime) {

			

		}

		//the target is stationary in this level, which does not shoot, so, 'enemyShoot' function is not necesary

		void enemyShoot(Enemy* enemy, int numEnemies, int enemyCurrentArrow, Arrow* enemyArrow, Player player)
			{	}
			
		*/


	int run()
	{
		enemy = new Enemy[1];
		enemyHealth = new RectangleShape[1];

		int temp;
		temp = Levels::run(1);
		return temp;
	}
};