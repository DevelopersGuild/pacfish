#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "Overlap.h"
#include <cstdlib>
using namespace std;
void handleEvent(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}
void handleCollision(sf::Sprite& PacFish, sf::Sprite& WallSprite, 
	sf::Sprite& WallSprite1, sf::Sprite& WallSprite2,
	sf::Sprite& WallSprite3, sf::Sprite& WallSprite4,
	sf::Sprite& WallSprite5, sf::Sprite& WallSprite6,
	sf::Sprite& WallSprite7, sf::Sprite& WallSprite8,
	sf::Sprite& WallSprite9, sf::Vector2f& position)
{
	if (overlap(PacFish, WallSprite))
	{
		PacFish.setPosition(position);
	}

	if (overlap(PacFish, WallSprite1))
	{
		PacFish.setPosition(position);
	}

	if (overlap(PacFish, WallSprite2))
	{
		PacFish.setPosition(position);
	}

	if (overlap(PacFish, WallSprite3))
	{
		PacFish.setPosition(position);
	}

	if (overlap(PacFish, WallSprite4))
	{
		PacFish.setPosition(position);
	}

	if (overlap(PacFish, WallSprite5))
	{
		PacFish.setPosition(position);
	}

	if (overlap(PacFish, WallSprite6))
	{
		PacFish.setPosition(position);
	}

	if (overlap(PacFish, WallSprite7))
	{
		PacFish.setPosition(position);
	}

	if (overlap(PacFish, WallSprite8))
	{
		PacFish.setPosition(position);
	}

	if (overlap(PacFish, WallSprite9))
	{
		PacFish.setPosition(position);
	}

}


void movement(sf::Sprite& PacFish, sf::Sprite& WallSprite,
	sf::Sprite& WallSprite1, sf::Sprite& WallSprite2,
	sf::Sprite& WallSprite3, sf::Sprite& WallSprite4,
	sf::Sprite& WallSprite5, sf::Sprite& WallSprite6,
	sf::Sprite& WallSprite7, sf::Sprite& WallSprite8,
	sf::Sprite& WallSprite9, sf::RenderWindow& window)
{
	float moveSpeed = 0.1, moveSpeedR = -0.1;
	sf::Vector2f currentPos = PacFish.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		moveSpeed /= 2.2;
		moveSpeedR /= 2.2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		moveSpeed *= 5;
		moveSpeedR *= 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		PacFish.move(0, moveSpeedR);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		PacFish.move(0, moveSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		PacFish.move(moveSpeed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		PacFish.move(moveSpeedR, 0);
	}

	handleCollision(PacFish, WallSprite,
		WallSprite1, WallSprite2,
		WallSprite3, WallSprite4,
		WallSprite5, WallSprite6,
	    WallSprite7, WallSprite8,
		WallSprite9, currentPos);
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Movement");
	sf::Texture Fish;
	Fish.loadFromFile(resourcePath() + "assets/sprites/character_sprite2.png");
	sf::Sprite PacFish;
	PacFish.setTexture(Fish);
	PacFish.setPosition(100, 300);
	PacFish.scale(0.05, 0.05);
	sf::Texture Wall;
	Wall.loadFromFile(resourcePath() + "assets/sprites/wall.jpg");
	sf::Sprite WallSprites[10];
	for (int i = 0; i < 10; i++) {
		WallSprites[i].setTexture(Wall);
		WallSprites[i].scale(0.3, 0.6);
	}

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

	while (window.isOpen())
	{
		handleEvent(window);
		window.clear();
		window.draw(PacFish);
		for (int j = 0; j < 10; j++) {
			window.draw(WallSprites[j]);
		}
		window.display();
		movement(PacFish, WallSprites[0], WallSprites[1],
			WallSprites[2], WallSprites[3], 
			WallSprites[4], WallSprites[5], 
			WallSprites[6], WallSprites[7], 
			WallSprites[8], WallSprites[9], window);
		
	}
	return 0;
}
