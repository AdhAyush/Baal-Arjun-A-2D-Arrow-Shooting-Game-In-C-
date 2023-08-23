
#include "Arrow.h"
#include <cmath>

using namespace sf;

// The constructor
Arrow::Arrow()
{

	m_ArrowTexture.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\arow.png");
	m_ArrowShape.setTexture(m_ArrowTexture);
	m_ArrowShape.setOrigin(25, 25);

	m_ArrowTexture1.loadFromFile("graphics/farow.png");
	m_ArrowShape1.setTexture(m_ArrowTexture1);
	m_ArrowShape1.setOrigin(25, 25);

}

// linear shoot
void Arrow::shoot(float startX, float startY) {
	

	//keep track of the Arrow
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;

	m_ArrowDistanceX = -m_ArrowSpeed;
	m_ArrowDistanceY = 0;

	m_ArrowShape.setRotation(180);

}

//overloading fire arrow
/* 
void Arrow::shoot(float startX, float startY, int f) {


	//keep track of the Arrow
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;

	m_ArrowDistanceX = -m_ArrowSpeed;
	m_ArrowDistanceY = 0;

	m_ArrowShape1.setRotation(180);

}

*/

void Arrow::shoot(float startX, float startY,
	float targetX, float targetY)
{
	// Keep track of the Arrow
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;

	

	// The algorithm
	/*
	1. Calculate slope   m = (y2-y1) / (x2-x1)
	2. Make slope positive
	3. Generally, m can be written as m = y/x
	4. so Vy = m*Vx  
	5. Vx^2 + Vy^2 = V^2
	6. Vx = V/sqrt(1 + m^2)         // this is magnitude of in positive x direction   i.e. magnitude of vector's x component
	7. Vy = m* Vx					// magniture of Y's component
	 
	 NOTE: This is magnitute of velocity in x and y direction
	 
	 For direction 
	if (targetX < startX)
	{
		m_ArrowDistanceX *= -1;
	}                           this ensures the direction of arrow

	Similarly, for Y direction
	if (targetY < startY)
	{
		m_ArrowDistanceY *= -1;
	}

	Finally, Velocity Vector is complete

	*/

	float gradient = (targetY - startY) / (targetX - startX);

	//making gradient positive 
	if (gradient < 0)
	{
		gradient *= -1;
	}

	//calculationg horizontal speed. NOTE: speed is magnitude 
	float Vx = m_ArrowSpeed / sqrt(1 + gradient * gradient);

	m_ArrowDistanceX = Vx;
	m_ArrowDistanceY = Vx * gradient;



	
	// Point the Arrow in the right direction
	if (targetX < startX)
	{
		m_ArrowDistanceX *= -1;
	}

	if (targetY < startY)
	{
		m_ArrowDistanceY *= -1;
	}


	// Finally, assign the results to the
	// member variables
	//m_XTarget = targetX;
	//m_YTarget = targetY;



	// Calculate the angle the arrow is facing
	float angle = (atan2(targetY - startY,
		targetX - startX)
		* 180) / 3.141;


	// Position the Arrow ready to be drawn
	m_ArrowShape.setPosition(m_Position);

	//set rotation towards the target
	m_ArrowShape.setRotation(angle);
}

// overloading for flaming arrow
void Arrow::shoot(float startX, float startY,
	float targetX, float targetY, int f)
{
	// Keep track of the Arrow
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;



	// The algorithm
	/*
	1. Calculate slope   m = (y2-y1) / (x2-x1)
	2. Make slope positive
	3. Generally, m can be written as m = y/x
	4. so Vy = m*Vx
	5. Vx^2 + Vy^2 = V^2
	6. Vx = V/sqrt(1 + m^2)         // this is magnitude of in positive x direction   i.e. magnitude of vector's x component
	7. Vy = m* Vx					// magniture of Y's component

	 NOTE: This is magnitute of velocity in x and y direction

	 For direction
	if (targetX < startX)
	{
		m_ArrowDistanceX *= -1;
	}                           this ensures the direction of arrow

	Similarly, for Y direction
	if (targetY < startY)
	{
		m_ArrowDistanceY *= -1;
	}

	Finally, Velocity Vector is complete

	*/

	float gradient = (targetY - startY) / (targetX - startX);

	//making gradient positive 
	if (gradient < 0)
	{
		gradient *= -1;
	}

	//calculationg horizontal speed. NOTE: speed is magnitude 
	float Vx = m_ArrowSpeed / sqrt(1 + gradient * gradient);

	m_ArrowDistanceX = Vx;
	m_ArrowDistanceY = Vx * gradient;




	// Point the Arrow in the right direction
	if (targetX < startX)
	{
		m_ArrowDistanceX *= -1;
	}

	if (targetY < startY)
	{
		m_ArrowDistanceY *= -1;
	}


	// Finally, assign the results to the
	// member variables
	//m_XTarget = targetX;
	//m_YTarget = targetY;



	// Calculate the angle the arrow is facing
	float angle = (atan2(targetY - startY,
		targetX - startX)
		* 180) / 3.141;


	// Position the Arrow ready to be drawn
	m_ArrowShape1.setPosition(m_Position);

	//set rotation towards the target
	m_ArrowShape1.setRotation(angle);
}


void Arrow::stop()
{
	m_InFlight = false;
}

bool Arrow::isInFlight()
{
	return m_InFlight;
}

FloatRect Arrow::getPosition()
{
	return m_ArrowShape.getGlobalBounds();
}

FloatRect Arrow::getPosition(int f)
{
	return m_ArrowShape1.getGlobalBounds();
}

Sprite Arrow::getSprite()
{
	return m_ArrowShape;
}

Sprite Arrow::getSprite(int f)
{
	return m_ArrowShape1;
}


void Arrow::setArrowspeed(int s) {
	m_ArrowSpeed = s;
}

void Arrow::update(float elapsedTime, Vector2f resolution)
{
	// Update the Arrow position variables
	m_Position.x += m_ArrowDistanceX * elapsedTime;
	m_Position.y += m_ArrowDistanceY * elapsedTime;

	// Move the Arrow
	m_ArrowShape.setPosition(m_Position);



	// Has the Arrow gone out of range ( which is display size for now)
	if (m_Position.x < 0 || m_Position.x > (resolution.x)||
		m_Position.y < 0 || m_Position.y > (resolution.y))
	{
		m_InFlight = false;
	}

}


//overloading flaming arrow
void Arrow::update(float elapsedTime, Vector2f resolution, int f)
{
	// Update the Arrow position variables
	m_Position.x += m_ArrowDistanceX * elapsedTime;
	m_Position.y += m_ArrowDistanceY * elapsedTime;

	// Move the Arrow
	m_ArrowShape1.setPosition(m_Position);



	// Has the Arrow gone out of range ( which is display size for now)
	if (m_Position.x < 0 || m_Position.x >(resolution.x) ||
		m_Position.y < 0 || m_Position.y >(resolution.y))
	{
		m_InFlight = false;
	}

}