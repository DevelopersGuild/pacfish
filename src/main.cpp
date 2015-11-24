#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "Overlap.h"
#include <cstdlib>
using namespace std;


const int NUM_WALLS = 38;

//FUNCTION
void positionWalls(sf::Sprite[]);
void handleEvent(sf::RenderWindow&);
void handleWalls(sf::Sprite&, sf::Vector2f&, sf::Sprite[], int);
void handleBullets(sf::Sprite&, sf::Vector2f&, vector <sf::Sprite>&);
void gameOverScreen(sf::RenderWindow&);



void movement(sf::Sprite& PacFish, sf::RenderWindow& window, sf::Sprite WallSprites[], int sizeOfArray, vector<sf::Sprite>& bullets)
{

	float moveSpeed = 4, moveSpeedR = -4;
	sf::Vector2f currentPos = PacFish.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		moveSpeed /= 2.2;
		moveSpeedR /= 2.2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		moveSpeed *= 2.2;
		moveSpeedR *= 2.2;
	}


	if (PacFish.getPosition().y >= 0 && PacFish.getPosition().y <= window.getSize().y)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			PacFish.move(0, moveSpeedR);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			PacFish.move(0, moveSpeed);
		}
		if (PacFish.getPosition().y <= 0)
			PacFish.setPosition(currentPos);
		if (PacFish.getPosition().y >= window.getSize().y - 56)
			PacFish.setPosition(currentPos);
	}

	if (PacFish.getPosition().x >= 0 && PacFish.getPosition().x <= window.getSize().x)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			PacFish.move(moveSpeed, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			PacFish.move(moveSpeedR, 0);
		}
		if (PacFish.getPosition().x <= 0)
			PacFish.setPosition(currentPos);
		if (PacFish.getPosition().x >= window.getSize().x - 66)
			PacFish.setPosition(currentPos);
	}


	// collisions
	handleWalls(PacFish, currentPos, WallSprites, sizeOfArray);
	handleBullets(PacFish, currentPos, bullets);

}


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "PacFish");
	window.setVerticalSyncEnabled(true);
	// PacFish
	sf::Texture Fish;
	Fish.loadFromFile(resourcePath() + "assets/sprites/character_sprite2.png");
	sf::Sprite PacFish;
	PacFish.setTexture(Fish);
	PacFish.setPosition(100, 300);
	PacFish.scale(0.03, 0.03);
	// walls
	sf::Texture Wall;
	Wall.loadFromFile(resourcePath() + "assets/sprites/wall.jpg");
	sf::Sprite WallSprites[NUM_WALLS];

	for (int i = 0; i < NUM_WALLS; i++)
	{
		WallSprites[i].setTexture(Wall);
		WallSprites[i].setScale(0.1, 0.4);
	}
	// create map
	positionWalls(WallSprites);
	// bullets
	sf::Texture bulletTexture;
	bulletTexture.loadFromFile(resourcePath() + "assets/sprites/bullet_sprite.png");

	vector <sf::Sprite> bullets;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			sf::Sprite bulletSprite;
			bulletSprite.setTexture(bulletTexture);
			bulletSprite.setPosition(100.f * i + 25.f, 100.f * j + 25.f); // place bullets
			bulletSprite.setScale(0.5, 0.5);
			bullets.push_back(bulletSprite);
		}
	}

	// game	
	bool isGameOver = false;
	while (window.isOpen())
	{
		handleEvent(window);
		window.clear();
		// draw walls
		for (int i = 0; i < NUM_WALLS; i++)
		{
			window.draw(WallSprites[i]);
		}
		
		if (isGameOver == false)
		{	//draw everything else
			for (int i = 0; i < bullets.size(); i++)
			{
				for (int j = 0; j < NUM_WALLS; j++)
				{
					if (overlap(bullets[i], WallSprites[j]))
						bullets.erase(bullets.begin() + i);
				}
				window.draw(bullets[i]);
			}
			window.draw(PacFish);

			window.display();
			movement(PacFish, window, WallSprites, NUM_WALLS, bullets);

		//game over requirments
			if (bullets.size() == 0)
				isGameOver = true;
		}

		if (isGameOver == true)
		{
			window.draw(PacFish);
			gameOverScreen(window);
		}
	}



	return 0;
}

void positionWalls(sf::Sprite WallSprites[NUM_WALLS])
{
	WallSprites[0].setPosition(120, 20);
	WallSprites[0].rotate(-90);
	WallSprites[1].setPosition(240, 20);
	WallSprites[1].rotate(-90);
	WallSprites[2].setPosition(0, 0);
	WallSprites[3].setPosition(360, 0);
	WallSprites[4].setPosition(120, 120);
	WallSprites[4].rotate(-90);
	WallSprites[5].setPosition(0, 120);
	WallSprites[6].setPosition(120, 120);
	WallSprites[7].setPosition(360, 120);
	WallSprites[8].setPosition(120, 240);
	WallSprites[8].rotate(-90);
	WallSprites[9].setPosition(240, 240);
	WallSprites[9].rotate(-90);
	WallSprites[10].setPosition(360, 240);
	WallSprites[10].rotate(-90);
	WallSprites[11].setPosition(0, 240);
	WallSprites[12].setPosition(240, 240);
	WallSprites[13].setPosition(480, 240);
	WallSprites[14].setPosition(30, 390);
	WallSprites[14].rotate(-90);
	WallSprites[15].setPosition(360, 360);
	WallSprites[15].rotate(-90);
	WallSprites[16].setPosition(0, 390);
	WallSprites[17].setPosition(360, 340);
	WallSprites[18].setPosition(120, 490);
	WallSprites[18].rotate(-90);
	WallSprites[19].setPosition(240, 490);
	WallSprites[19].rotate(-90);
	WallSprites[20].setPosition(0, 510);
	WallSprites[21].setPosition(30, 610);
	WallSprites[21].rotate(-90);
	WallSprites[22].setPosition(150, 610);
	WallSprites[22].rotate(-90);
	WallSprites[23].setPosition(270, 610);
	WallSprites[23].rotate(-90);
	WallSprites[24].setPosition(390, 610);
	WallSprites[24].rotate(-90);
	WallSprites[25].setPosition(480, 360);
	WallSprites[26].setPosition(600, 480);
	WallSprites[27].setPosition(600, 480);
	WallSprites[27].rotate(-90);
	WallSprites[28].setPosition(600, 360);
	WallSprites[28].rotate(-90);
	WallSprites[29].setPosition(720, 360);
	WallSprites[29].rotate(-90);
	WallSprites[30].setPosition(600, 240);
	WallSprites[30].rotate(-90);
	WallSprites[31].setPosition(600, 120);
	WallSprites[32].setPosition(480, 120);
	WallSprites[32].rotate(-90);
	WallSprites[33].setPosition(480, 120);
	WallSprites[34].setPosition(720, 120);
	WallSprites[34].rotate(-90);
	WallSprites[35].setPosition(600, 90); //filler for 31
	WallSprites[36].setPosition(0, 390); //filler for 14
	WallSprites[36].rotate(-90);
	WallSprites[37].setPosition(360, 370); //filler for 17
}

void handleEvent(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void handleWalls(sf::Sprite& PacFish, sf::Vector2f& position, sf::Sprite WallSprites[], int sizeOfArray)
{
	for (int i = 0; i < sizeOfArray; i++)
	{
		if (overlap(PacFish, WallSprites[i]))
		{
			PacFish.setPosition(position);
		}
	}
}

void handleBullets(sf::Sprite& PacFish, sf::Vector2f& position, vector <sf::Sprite>& bullets)
{

	for (int i = 0; i < bullets.size(); i++)
	{
		if (overlap(PacFish, bullets[i]))
		{
			bullets.erase(bullets.begin() + i);
		}
	}

}


//game over
void gameOverScreen(sf::RenderWindow& window)
{
	sf::Font font;
	font.loadFromFile(resourcePath() + "assets/prstartk.ttf");
	sf::Text OverMessage("Game Over!", font);
	OverMessage.setColor(sf::Color::Red);

	window.draw(OverMessage);
	window.display();

}