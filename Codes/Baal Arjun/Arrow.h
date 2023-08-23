#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Arrow
{
private:
	// Where is the Arrow?
	Vector2f m_Position;

	// What each Arrow looks like
	Texture m_ArrowTexture;
	Sprite m_ArrowShape;

	// for flaming arrow
	Texture m_ArrowTexture1;
	Sprite m_ArrowShape1;

	// Is this Arrow currently whizzing through the air
	bool m_InFlight = false;

	// How fast does a Arrow travel?
	float m_ArrowSpeed = 1000;

	// What fraction of 1 pixel does the Arrow travel, 
	// Horizontally and vertically each frame?
	// These values will be derived from m_ArrowSpeed
	float m_ArrowDistanceX;
	float m_ArrowDistanceY;

	// Where is this Arrow headed to?
	float m_XTarget;
	float m_YTarget;

	// Some boundaries so the Arrow doesn't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

	// Public function prototypes go here
public:
	// The constructor
	Arrow();

	// Stop the Arrow
	void stop();

	// Returns the value of m_InFlight
	bool isInFlight();

	// Launch a new Arrow
	void shoot(float startX, float startY,
		float xTarget, float yTarget);
	void shoot(float startX, float startY);

	// Tell the calling code where the Arrow is in the world
	FloatRect getPosition();

	// Change the arrow speed as per need
	void setArrowspeed(int s);

	// Return the actual sprite (for drawing)
	Sprite getSprite();

	// Update the Arrow each frame
	void update(float elapsedTime, Vector2f resolution);


	// overloaded function
	void shoot(float startX, float startY, int f);
	void shoot(float startX, float startY, float targetX, float targetY, int f);
	FloatRect getPosition(int f);
	Sprite getSprite(int f);
	void update(float elapsedTime, Vector2f resolution, int f);

};
