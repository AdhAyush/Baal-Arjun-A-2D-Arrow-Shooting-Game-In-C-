#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Sudarshan
{
private:
	// Where is the Sudarshan?
	Vector2f m_Position;

	// What Sudarshan looks like
	Texture m_SudarshanTexture;
	Sprite m_SudarshanShape;

	// Is this Arrow currently whizzing through the air
	bool m_InFlight = false;

	// How fast does a Arrow travel?
	float m_SudarshanSpeed = 900;

	// What fraction of 1 pixel does the Arrow travel, 
	// Horizontally and vertically each frame?
	// These values will be derived from m_ArrowSpeed
	float m_SudarshanDistanceX;
	float m_SudarshanDistanceY;

	float angle;
	float angleSudarshan = 0;

	// Where is this Arrow headed to?
	float m_XTarget;
	float m_YTarget;

	// Some boundaries so the Arrow doesn't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

	//amplitude and frequency of the sudarshan
	int amp = 100;
	int freq = 1;

	float time = 0;

	// Public function prototypes go here
public:
	// The constructor
	Sudarshan();

	// Stop the Arrow
	void stop();

	// Returns the value of m_InFlight
	bool isInFlight();

	// Launch a new Arrow
	void shootSudarshan(float startX, float startY,
		float xTarget, float yTarget);


	// Tell the calling code where the Sudarshan is in the world
	FloatRect getPosition();
	/*FloatRect getPosition(int f);*/

	// Change the arrow speed as per need
	void setSudarshanspeed(int s);

	// Return the actual sprite (for drawing)
	Sprite getSprite();
	//Sprite getSprite(int f);


	// Update the Sudarshan each frame
	void update(float elapsedTime, Vector2f resolution);
	//void update(float elapsedTime, Vector2f resolution, int f);

};
