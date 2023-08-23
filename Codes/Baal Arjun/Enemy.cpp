#include "Enemy.h"
#include <cstdlib>
#include <ctime>

using namespace std;


void Enemy::spawn(float startX, float startY, int type, int timeInterval)
{
	enemyShootInterval = timeInterval;

	switch (type)
	{
	case 0:
		// Enemy_Level1
		m_Texture.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\Enemy_Level1.png");
		m_Sprite.setTexture(m_Texture);

		m_Speed = 40;
		m_Health = 5;
		m_MaxHealth = 5;
		break;

	case 1:
		// Enemy_Level2
		m_Texture.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\Enemy_Level2.png");
		m_Sprite.setTexture(m_Texture);

		m_Speed = 30;
		m_Health = 8;
		m_MaxHealth = 8;
		break;

	case 2:
		// Enemy_Level3
		m_Texture.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\Enemy_Level3.png");
		m_Sprite.setTexture(m_Texture);

		m_Speed = 20;
		m_Health = 10;
		m_MaxHealth = 10;

		break;
	default:
		break;
	}

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
	
}

bool Enemy::hit()
{
	m_Health--;

	if (m_Health <= 0)
	{
		// dead
		m_Alive = false;
		m_Texture.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\blood.png");
		m_Sprite.setTexture(m_Texture);

		return true;
	}

	// injured but not dead yet
	return false;
}


//overloading for sudarshan
bool Enemy::hit(int s)
{
	// dead when hit by sudarshan chakra
	m_Alive = false;
	m_Texture.loadFromFile("graphics/blood.png");
	m_Sprite.setTexture(m_Texture);

	return true;

}

bool Enemy::isAlive()
{
	return m_Alive;
}

FloatRect Enemy::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Enemy::getCenter()
{
	return m_Position;
}

Sprite Enemy::getSprite()
{
	return m_Sprite;
}

void Enemy::update(float elapsedTime,
	Vector2f playerLocation, Vector2f resolution)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;


// m_Position.x = resolution.x /1.5;
//	m_Position.y = resolution.y / 2;


	 // Update the Enemy position variables
	 if (playerX > m_Position.x)
	 {
	 	m_Position.x = m_Position.x +
	 		m_Speed * elapsedTime;
	 }

	 if (playerY > m_Position.y)
	 {
	 	m_Position.y = m_Position.y +
 		m_Speed * elapsedTime;
	 }

	 if (playerX < m_Position.x)
	 {
	 	m_Position.x = m_Position.x -
	 		m_Speed * elapsedTime;
	 }

	 if (playerY < m_Position.y)
	 {
	 	m_Position.y = m_Position.y -
	 	m_Speed * elapsedTime;
	 }

	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;

	 m_Sprite.setRotation(angle );


}

void Enemy::updateLinear(float elapsedTime, float x_Lim) {
	
	if (!(m_Position.x < x_Lim)) {

	m_Position.x -= m_Speed * elapsedTime;
	m_Sprite.setPosition(m_Position);

	}
	

}

void Enemy::updateVertical(float elapsedTime, float y_Max, float y_Min) {
	if (m_Position.y < (y_Min + 50)) {
		m_Speed *= -1;
	}

	if (m_Position.y > (y_Max - 50)) {
		m_Speed *= -1;
	}
	
	m_Position.y += m_Speed * elapsedTime;
	m_Sprite.setPosition(m_Position);
}



float Enemy::getHealth() {
	return m_Health;
}

float Enemy::getMaxHealth() {
	return m_MaxHealth;
}

void Enemy::setSpeed(int s) {
	m_Speed = s;
}

void Enemy::operator++(int) {
	timeSinceLastShoot++;
}

bool Enemy::lastShootGreaterThanInterval() {
	if (timeSinceLastShoot > enemyShootInterval)
		return true;
	else
		return false;
}

void Enemy::resetTimeSinceLastShoot() {
	timeSinceLastShoot = 0;
}