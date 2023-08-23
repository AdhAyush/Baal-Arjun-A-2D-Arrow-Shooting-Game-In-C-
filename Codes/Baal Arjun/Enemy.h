#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
private:
	// Where is this Enemy?
	Vector2f m_Position;

	//texture for the Enemy
	Texture m_Texture;

	// A sprite for the Enemy
	Sprite m_Sprite;

	// How fast can this one run/crawl?
	float m_Speed;

	// How much health has it got?
	float m_Health;

	//maximum health
	float m_MaxHealth;

	// Is it still alive?
	bool m_Alive;


	int enemyShootInterval ;
	int timeSinceLastShoot = 0;

	// Public prototypes go here	
public:

	// Handle when a bullet hits a Enemy
	bool hit();

	//for when sudarshan chakra hits enemy
	bool hit(int s);

	// Find out if the Enemy is alive
	bool isAlive();

	// Spawn a new Enemy
	void spawn(float startX, float startY, int type, int timeInterval);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	Vector2f getCenter();

	float getHealth();

	float getMaxHealth();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Update the Enemy each frame
	void update(float elapsedTime, Vector2f playerLocation, Vector2f resolution);

	void updateLinear(float elapsedTime, float x_Lim);

	void updateVertical(float elapsedTime, float y_Max, float y_Min);

	void setSpeed(int a);
	// Update 
//	void update(float elapsedTime, Vector2f resolution);

	void operator++(int);

	bool lastShootGreaterThanInterval();

	void resetTimeSinceLastShoot();
	
};



