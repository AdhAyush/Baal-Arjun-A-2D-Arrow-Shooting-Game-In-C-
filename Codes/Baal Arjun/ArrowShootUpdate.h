#pragma once
#include "SFML/Graphics.hpp"
#include "Arrow.h"
#include "Enemy.h"
#include "Player.h"

using namespace sf;

void shootLinear(Enemy& enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow);
void shootTowardsPlayer(Enemy& enemy, int numEnemies, int& enemyCurrentArrow, Arrow* enemyArrow, Player player);
