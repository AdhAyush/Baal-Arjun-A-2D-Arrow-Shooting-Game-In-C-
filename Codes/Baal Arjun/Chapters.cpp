#include <SFML/Graphics.hpp>
#include <sstream>
#include "Chapters.h"
#include "Levels.h"
#include "level1.cpp"
#include "level2.cpp"
#include "level3.cpp"
#include "level4.cpp"
#include "level5.cpp"
#include "level6.cpp"
#include "level7.cpp"
#include "level8.cpp"
#include "level9.cpp"
#include "level10.cpp"
#include <iostream>

using namespace std;
using namespace sf;


Chapters::Chapters()
{
	state = State::LEVELING_UP;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	RenderWindow window;

	//defining the chapters in the screen
	font.loadFromFile("fonts/times.ttf");

	//1st 2 levels are unlocked so the 2 values are set 1 and others are set to 1
	for (int i = 0; i < 11; i++)
	{
		if (i == 0 || i == 1)
		{
			unlock_level[i] = 1;
		}
		//if
		//{
		unlock_level[i] = 1;
		//}
	}
	//lock sprites
	lockTexture.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\locked.png");
	lockSprite.setTexture(lockTexture);

	//unlock sprite
	unlockTexture.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\unlocked.png");
	unlockSprite.setTexture(unlockTexture);


	//Chapter main heading
	Heading.setFont(font);
	Heading.setCharacterSize(50);
	Heading.setFillColor(Color::Red);
	Heading.setPosition(0, 0);
	Heading.setString("LEVEL SELECTION");

	//levels
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(30);
	levelUpText.setFillColor(Color::White);
	levelUpText.setPosition(0, 100);

	levelUpStream <<
		"\nCHAPTER A - PRACTICE" <<
		"\n1- level 1" <<
		"\n2- level 2" <<
		"\n\nCHAPTER B - FIGHTS" <<
		"\n3- level 3" <<
		"\n4- level 4" <<
		"\n5- level 5" <<
		"\n\nCHAPTER C - WAR" <<
		"\n6- level 6" <<
		"\n7- level 7" <<
		"\n8- level 8" <<
		"\n9- level 9" <<
		"\n10- level 10";
	levelUpText.setString(levelUpStream.str());


	yadaBuffer.loadFromFile("sounds/yada.mp3");
	yada.setBuffer(yadaBuffer);

}



int Chapters::chapter_select()
{
	yada.play();

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Level Selection", Style::Fullscreen);


	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	Sprite chapterSprite;
	//Menu.setSize(Vector2f(resolution.x, resolution.y));
	Texture textureChapter;
	textureChapter.loadFromFile("C:\\Users\\ayush\\OneDrive\\Desktop\\Baal arjun\\Codes\\Baal Arjun\\graphics\\ch.jpg");
	chapterSprite.setTexture(textureChapter);

	float scaleX = static_cast<float>(window.getSize().x) / textureChapter.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / textureChapter.getSize().y;

	//Set the smooth property of the texture to avoid pixelation
	textureChapter.setSmooth(true);
	chapterSprite.setScale(scaleX, scaleY);

	int Y_offset = 0;

	//coordinates of level selections
	Vector2i level_x(2, 200);
	Vector2i level1_y(160, 200);
	Vector2i level2_y(210, 250);
	Vector2i level3_y(315, 345);
	Vector2i level4_y(355, 380);
	Vector2i level5_y(390, 420);
	Vector2i level6_y(490, 520);
	Vector2i level7_y(530, 550);
	Vector2i level8_y(570, 590);
	Vector2i level9_y(600, 630);
	Vector2i level10_y(650, 690);

	//added polymorphism
	Levels* lvl[10];
	lvl[0] = new level1;
	lvl[1] = new level2;
	lvl[2] = new level3;
	lvl[3] = new level4;
	lvl[4] = new level5;
	lvl[5] = new level6;
	lvl[6] = new level7;
	lvl[7] = new level8;
	lvl[8] = new level9;
	lvl[9] = new level10;

	//objects 
	Chapters c;

	while (window.isOpen())
	{
		Event event;

		//handle quitting


		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		/*
			if (event.key.code == Keyboard::Escape)
			{
				cout << "Game closed!" << endl;
			}
		*/
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				yada.stop();
				window.close();
				return 0;
			}

			/*if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up)
				{
					c.moveUp();
					break;
				}
				if (event.key.code == Keyboard::Down)
				{
					c.moveDown();
					break;
				}*/

		}
		/*
			//code for seeing coordinates
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			std::cout << "X: " << mousePos.x << " | Y: " << mousePos.y << std::endl;
		*/

		//code for opening chapters screen for opening levels button by clicking with mouse or using keys
		//level 1
		if (event.type == Event::MouseButtonReleased || event.key.code == Keyboard::Num1)
		{
			std::cout << "x coordinate " << event.mouseButton.x << "   y coordinate " << event.mouseButton.y << std::endl;
			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Num1)
			{
				if (event.key.code == Keyboard::Num1 || ((level_x.x <= event.mouseButton.x) && (event.mouseButton.x <= level_x.y)
					&& ((level1_y.x <= event.mouseButton.y) && (event.mouseButton.y <= level1_y.y))))
				{
					//window.close();
					int levl1 = 1;

					if (unlock_level[0] == 1) {
						yada.stop();
						levl1 = lvl[0]->run();
						delete(lvl[0]);
						lvl[0] = new level1;

						yada.play();


					}
					state = State::LEVELING_UP;

					/*int levl1;
					level1 l1;
					levl1 = l1.run();
					state = State::LEVELING_UP;*/
					if (levl1 == 0)
					{
						unlock_level[1] = 1; //unlocks level 3
					}

				}

/*
				//code for escaping out of the level selection window
				if (event.key.code == Keyboard::Escape)
				{
					window.close();

				}
*/
				//break;
			}


		}//endif

/*
		// Handle the player levelling up
		if (event.key.code == Keyboard::Num1) // modify this code to look for level selected i..e.  (if level ==1 ) => body remains same
		{
			int levl1;
			level1 l1;
			levl1 = l1.run();

			state = State::LEVELING_UP;

			break;
		}

*/
//level2
		if (event.type == Event::MouseButtonReleased || event.key.code == Keyboard::Num2)
		{

			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Num2)
			{
				if (event.key.code == Keyboard::Num2 || ((level_x.x <= event.mouseButton.x) && (event.mouseButton.x <= level_x.y)
					&& ((level2_y.x <= event.mouseButton.y) && (event.mouseButton.y <= level2_y.y))))
				{

					int levl2 = 1;
					if (unlock_level[1] == 1) {
						yada.stop();
						levl2 = lvl[1]->run();
						delete(lvl[1]);
						lvl[1] = new level2;
						yada.play();
						/*cout << levl2 << endl;*/

					}


					//code for unlocking next level
					//cout << levl2 << endl;				
					if (levl2 == 0)
					{
						unlock_level[2] = 1; //unlocks level 3
					}
					//break;
					state = State::LEVELING_UP;


				}


			}
		}//endif

		 //level 3
		if (event.type == Event::MouseButtonReleased || event.key.code == Keyboard::Num3)
		{	
			int levl3 = 1;
			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Num3)
			{
				if (event.key.code == Keyboard::Num3 || ((level_x.x <= event.mouseButton.x) && (event.mouseButton.x <= level_x.y)
					&& ((level3_y.x <= event.mouseButton.y) && (event.mouseButton.y <= level3_y.y))))
				{


					if (unlock_level[2] == 1) {
						yada.stop();
						levl3 = lvl[2]->run();
						delete(lvl[2]);
						lvl[2] = new level3;
						yada.play();

					}


					//code for unlocking next level
					if (levl3 == 0)
					{
						unlock_level[4] = 1; //unlocks level 4
					}
					state = State::LEVELING_UP;


				}
			}

		}//endif

		//level 4
		if (event.type == Event::MouseButtonReleased || event.key.code == Keyboard::Num4)
		{
			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Num4)
			{
				if (event.key.code == Keyboard::Num4 || ((level_x.x <= event.mouseButton.x) && (event.mouseButton.x <= level_x.y)
					&& ((level4_y.x <= event.mouseButton.y) && (event.mouseButton.y <= level4_y.y))))
				{
					int levl4 = 1;

					if (unlock_level[4] == 1) {
						yada.stop();
						levl4 = lvl[3]->run();
						delete(lvl[3]);
						lvl[3] = new level4;
						yada.play();
					}

					state = State::LEVELING_UP;
					//code for unlocking next level

					if (levl4 == 0)
					{
						// unlock_level[4] = 1; // should unlock level 5 but it didnt
						unlock_level[5] = 1; //this unlocked level 5 and 6 for reason unknown , should have unlocked 6 onlys

					}


				}
			}
		}//endif

		//level 5
		if (event.type == Event::MouseButtonReleased || event.key.code == Keyboard::Num5)
		{
			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Num5)
			{
				if (event.key.code == Keyboard::Num5 || ((level_x.x <= event.mouseButton.x) && (event.mouseButton.x <= level_x.y)
					&& ((level5_y.x <= event.mouseButton.y) && (event.mouseButton.y <= level5_y.y))))
				{
					int levl5 = 1;

					if (unlock_level[5] == 1) {
						yada.stop();
						levl5 = lvl[4]->run();
						delete(lvl[4]);
						lvl[4] = new level5;
						yada.play();
					}

					state = State::LEVELING_UP;
					//code for unlocking next level

					if (levl5 == 0)
					{
						unlock_level[6] = 1; //unlocks level 6
					}

				}
			}
		}//endif

		//level 6
		if (event.type == Event::MouseButtonReleased || event.key.code == Keyboard::Num6)
		{
			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Num6)
			{
				if (event.key.code == Keyboard::Num6 || ((level_x.x <= event.mouseButton.x) && (event.mouseButton.x <= level_x.y)
					&& ((level6_y.x <= event.mouseButton.y) && (event.mouseButton.y <= level6_y.y))))
				{
					int levl6 = 1;

					if (unlock_level[5] == 1) {
						yada.stop();
						levl6 = lvl[5]->run();
						delete(lvl[5]);
						lvl[5] = new level6;
						yada.play();
					}

					state = State::LEVELING_UP;

					//code for unlocking next level

					if (levl6 == 0)
					{
						unlock_level[7] = 1; //unlocks level 7
					}



				}
			}
		}//endif

		//level 7
		if (event.type == Event::MouseButtonReleased || event.key.code == Keyboard::Num7)
		{
			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Num7)
			{
				if (event.key.code == Keyboard::Num7 || ((level_x.x <= event.mouseButton.x) && (event.mouseButton.x <= level_x.y)
					&& ((level7_y.x <= event.mouseButton.y) && (event.mouseButton.y <= level7_y.y))))
				{
					int levl7 = 1;

					if (unlock_level[6] == 1) {
						yada.stop();
						levl7 = lvl[6]->run();
						delete(lvl[6]);
						lvl[6] = new level7;
						yada.play();
					}

					state = State::LEVELING_UP;
					//code for unlocking next level

					if (levl7 == 0)
					{
						unlock_level[8] = 1; //unlocks level 8
					}


				}
			}
		}//endif

		//level 8
		if (event.type == Event::MouseButtonReleased || event.key.code == Keyboard::Num8)
		{
			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Num8)
			{
				if (event.key.code == Keyboard::Num8 || ((level_x.x <= event.mouseButton.x) && (event.mouseButton.x <= level_x.y)
					&& ((level8_y.x <= event.mouseButton.y) && (event.mouseButton.y <= level8_y.y))))
				{
					int levl8 = 1;

					if (unlock_level[7] == 1) {
						yada.stop();
						levl8 = lvl[7]->run();
						delete(lvl[7]);
						lvl[7] = new level8;
						yada.play();
					}

					state = State::LEVELING_UP;
					//code for unlocking next level

					if (levl8 == 0)
					{
						unlock_level[9] = 1; //unlocks level 9
					}

				}
			}
		}//endif

		//level 9
		if (event.type == Event::MouseButtonReleased || event.key.code == Keyboard::Num9)
		{
			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Num9)
			{
				if (event.key.code == Keyboard::Num9 || ((level_x.x <= event.mouseButton.x) && (event.mouseButton.x <= level_x.y)
					&& ((level9_y.x <= event.mouseButton.y) && (event.mouseButton.y <= level9_y.y))))
				{
					int levl9 = 1;

					if (unlock_level[8] == 1) {
						yada.stop();
						levl9 = lvl[8]->run();
						delete(lvl[8]);
						lvl[8] = new level9;
						yada.play();
					}

					state = State::GAME_OVER;
					//code for unlocking next level

				}
			}
		}//endif

				//level 10
		if (event.type == Event::MouseButtonReleased || event.key.code == Keyboard::Num0)
		{
			if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Num0)
			{
				if (event.key.code == Keyboard::Num9 || ((level_x.x <= event.mouseButton.x) && (event.mouseButton.x <= level_x.y)
					&& ((level10_y.x <= event.mouseButton.y) && (event.mouseButton.y <= level10_y.y))))
				{
					int levl10 = 1;

					if (unlock_level[9] == 1) {
						yada.stop();
						levl10 = lvl[9]->run();
						delete(lvl[9]);
						lvl[9] = new level10;
						yada.play();
					}

					state = State::GAME_OVER;
					//code for unlocking next level

				}
			}
		}//endif

		window.clear();
		window.draw(chapterSprite);

		/*for (int i = 0; i < no_of_chapters; i++)
		{
			window.draw(chapter[i]);

		}*/
		window.draw(Heading);
		window.draw(levelUpText);

		//DRAWIG LOCKED AND UNLOCKED ICONS FOR LEVELS
		for (int i = 0; i < 2; i++)
		{
			//always draws the unlocked icon of first 2 levels
			unlockSprite.setPosition(250, 175 + Y_offset);
			Y_offset += 40;
			window.draw(unlockSprite);
		}
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				if (unlock_level[2 + i] == 1)   // draws unlocked icon if the level is unlocked i.e the array has 1 value
				{
					Y_offset += 65;

					//drawing new unlocked icon
					unlockSprite.setPosition(250, 160 + Y_offset);
					window.draw(unlockSprite);

				}
				if (unlock_level[2 + i] == 0)						// draws locked icon if the level is locked	i.e the array has 0 value
				{
					lockSprite.setColor(sf::Color(255, 255, 255, 100)); // make lock visible
					Y_offset += 65;
					lockSprite.setPosition(250, 160 + Y_offset);
					window.draw(lockSprite);
				}
			}
			else
			{
				if (unlock_level[2 + i] == 1)   // draws unlocked icon if the level is unlocked
				{

					unlockSprite.setPosition(250, 160 + Y_offset);
					Y_offset += 40;
					window.draw(unlockSprite);



				}
				else                       //draws locked icon if the level is locked
				{
					lockSprite.setColor(sf::Color(255, 255, 255, 100)); // make lock transparent
					lockSprite.setPosition(250, 160 + Y_offset);
					Y_offset += 40;
					window.draw(lockSprite);
				}


			}
		}



		for (int i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				if (unlock_level[5 + i] == 1)   // draws unlocked icon if the level is unlocked i.e the array has 1 value
				{
					Y_offset += 65;

					//drawing new unlocked icon
					unlockSprite.setPosition(250, 160 + Y_offset);
					window.draw(unlockSprite);

				}
				if (unlock_level[5 + i] == 0)						// draws locked icon if the level is locked	i.e the array has 0 value
				{
					lockSprite.setColor(sf::Color(255, 255, 255, 255)); // make lock visible
					Y_offset += 65;
					lockSprite.setPosition(250, 160 + Y_offset);
					window.draw(lockSprite);
				}
			}
			else
			{
				if (unlock_level[5 + i] == 1)   // draws unlocked icon if the level is unlocked
				{

					unlockSprite.setPosition(250, 160 + Y_offset);
					Y_offset += 40;
					window.draw(unlockSprite);



				}
				else                       //draws locked icon if the level is locked
				{
					lockSprite.setColor(sf::Color(255, 255, 255, 200)); // make lock transparent
					lockSprite.setPosition(260, 160 + Y_offset);
					Y_offset += 40;
					window.draw(lockSprite);
				}


			}
		}




		Y_offset = 0;


		window.display();
	}
	return 0;
}
