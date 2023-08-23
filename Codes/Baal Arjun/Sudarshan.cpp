
#include "Sudarshan.h"
#include <cmath>

using namespace sf;

// The constructor
Sudarshan::Sudarshan()
{

	m_SudarshanTexture.loadFromFile("graphics/sudarshan.png");
	m_SudarshanShape.setTexture(m_SudarshanTexture);
	m_SudarshanShape.setOrigin(25, 25);

}

void Sudarshan::shootSudarshan(float startX, float startY, float targetX, float targetY) {


	//keep track of the Sudarshan
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;

	m_SudarshanDistanceX = -m_SudarshanSpeed;
	m_SudarshanDistanceY = 0;

	m_SudarshanShape.setRotation(180);

	
	float gradient = (targetY - startY) / (targetX - startX);

	//making gradient positive 
	if (gradient < 0)
	{
		gradient *= -1;
	}

	//calculationg horizontal speed. NOTE: speed is magnitude 
	float Vx = m_SudarshanSpeed / sqrt(1 + gradient * gradient);

	m_SudarshanDistanceX = Vx;
	m_SudarshanDistanceY = Vx * gradient;




	// Point the Sudarshan in the right direction
	if (targetX < startX)
	{
		m_SudarshanDistanceX *= -1;
	}

	if (targetY < startY)
	{
		m_SudarshanDistanceY *= -1;
	}

	// Calculate the angle the arrow is facing
	angle = (atan2(targetY - startY,
		targetX - startX)
		* 180) / 3.141;


	// Position the Arrow ready to be drawn
	m_SudarshanShape.setPosition(m_Position);

	//set rotation towards the target
	m_SudarshanShape.setRotation(angle);
}



void Sudarshan::stop()
{
	m_InFlight = false;
}

bool Sudarshan::isInFlight()
{
	return m_InFlight;
}

FloatRect Sudarshan::getPosition()
{
	return m_SudarshanShape.getGlobalBounds();
}




Sprite Sudarshan::getSprite()
{
	return m_SudarshanShape;
}




void Sudarshan::update(float elapsedTime, Vector2f resolution)
{
	time += elapsedTime;

	m_Position.x += m_SudarshanDistanceX * elapsedTime;
	m_Position.y += m_SudarshanDistanceY * elapsedTime;

	float x;
	float y;

	x = m_Position.x + amp * sin(2 * 3.1416 * freq * time) * cos(90 - angle);
	y = m_Position.y - amp * sin(2 * 3.1416 * freq * time) * sin(90 - angle);

	m_SudarshanShape.setPosition(Vector2f(x,y));

	// Has the Sudarshan gone out of range ( which is display size for now)
	if (m_Position.x < 0 || m_Position.x >(resolution.x) ||
		m_Position.y < 0 || m_Position.y >(resolution.y))
	{
		m_InFlight = false;
	}

}
