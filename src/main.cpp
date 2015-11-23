#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "Overlap.h"
#include <cstdlib>
using namespace std;


const int NUM_WALLS = 10;

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
		if (PacFish.getPosition().x >= window.getSize().x - 111)
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
	PacFish.scale(0.05, 0.05);
	// walls
	sf::Texture Wall;
	Wall.loadFromFile(resourcePath() + "assets/sprites/wall.jpg");
	sf::Sprite WallSprites[NUM_WALLS];

	for (int i = 0; i < NUM_WALLS; i++)
	{
		WallSprites[i].setTexture(Wall);
		WallSprites[i].setScale(0.3, 0.6);
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
	WallSprites[0].setPosition(310, 300);
	WallSprites[0].rotate(-90);
	WallSprites[1].setPosition(450, 290);
	WallSprites[2].setPosition(0, 500);
	WallSprites[3].setPosition(700, 300);
	WallSprites[4].setPosition(0, 300);
	WallSprites[4].rotate(-90);
	WallSprites[5].setPosition(220, 500);
	WallSprites[6].setPosition(310, 80);
	WallSprites[7].setPosition(620, 180);
	WallSprites[7].rotate(-90);
	WallSprites[8].setPosition(220, 80);
	WallSprites[8].rotate(-90);
	WallSprites[9].setPosition(700, 290);
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