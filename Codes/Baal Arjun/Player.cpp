
#include "player.h"

Player::Player()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	

	// Associate a texture with the sprite
	// !!Watch this space!!
	

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	//setting texture for the player
	m_Texture.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\player.png");
	m_Sprite.setTexture(m_Texture);

	//making health of the player maximum when spawning
	m_Health = m_MaxHealth;

	// Place the player in the middle of the arena
	m_Position.x = resolution.x / 8;
	m_Position.y = resolution.y / 2;

	// Copy the details of the arena to the player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	// Remember how big the tiles are in this arena
	m_TileSize = tileSize;

	// Strore the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;

	m_Sprite.setPosition(m_Position);

}

Time Player::getLastHitTime()
{
	return m_LastHit;
}


void Player::hit()
{
	m_Health -= 10;

	if (m_Health <= 0)
	{
		// dead
		m_Texture.loadFromFile("graphics/blood.png");
		m_Sprite.setTexture(m_Texture);
	}

}


FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation();
}

Sprite Player::getSprite()
{
	return m_Sprite;
}


float Player::getHealth()
{
	return m_Health;
}


void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}

//returns max health
float Player::getMaxHealth() {
	return m_MaxHealth;
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{

	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);



	// Keep the player in the arena
	if (m_Position.x > m_Arena.width - m_TileSize)
	{
		m_Position.x = m_Arena.width - m_TileSize;
	}

	if (m_Position.x < m_Arena.left + m_TileSize)
	{
		m_Position.x = m_Arena.left + m_TileSize;
	}

	if (m_Position.y > m_Arena.height - m_TileSize)
	{
		m_Position.y = m_Arena.height - m_TileSize;
	}

	if (m_Position.y < m_Arena.top + m_TileSize)
	{
		m_Position.y = m_Arena.top + m_TileSize;
	}

	// Calculate the angle the player is facing
	float angle =  (atan2(mousePosition.y - m_Position.y,
		mousePosition.x - m_Position.x)
		* 180) / 3.141;

	m_Sprite.setRotation(angle + 270);
}


