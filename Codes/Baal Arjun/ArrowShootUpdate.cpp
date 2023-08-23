#include "ArrowShootUpdate.h"
#include <iostream>


void shootLinear(Enemy& enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow) {
	enemyArrow[enemyCurrentArrow].setArrowspeed(300);

	std::cout << "Shoot Linear"<<std::endl;

	enemyArrow[enemyCurrentArrow].shoot(
		enemy.getCenter().x, enemy.getCenter().y);


	enemyCurrentArrow++;
	if (enemyCurrentArrow > 99)
	{
		enemyCurrentArrow = 0;
	}

	enemy.resetTimeSinceLastShoot();
}

void shootTowardsPlayer(Enemy& enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow, Player player) {
	enemyArrow[enemyCurrentArrow].setArrowspeed(500);

	std::cout << " Shoot towards player"<<std::endl;

	enemyArrow[enemyCurrentArrow].shoot(
		enemy.getCenter().x, enemy.getCenter().y,
		player.getCenter().x, player.getCenter().y);


	enemyCurrentArrow++;
	if (enemyCurrentArrow > 99)
	{
		enemyCurrentArrow = 0;
	}
	enemy.resetTimeSinceLastShoot();
}