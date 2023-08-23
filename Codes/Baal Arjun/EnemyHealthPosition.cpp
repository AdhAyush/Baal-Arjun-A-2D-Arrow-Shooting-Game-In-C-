#include "EnemyHealthPosition.h"

void updateEnemyHealthBar(Enemy &enemy, RectangleShape &enemyHealth) {

	enemyHealth.setSize(Vector2f(enemy.getHealth() / enemy.getMaxHealth() * 20, 3));
	enemyHealth.setPosition(enemy.getCenter().x, enemy.getCenter().y - 10);
	enemyHealth.setFillColor(Color::Red);

}