#include "powerup.h"
#include <iostream>

using namespace std;

powerup::powerup(sf::Vector2f position)
{
	powerupType = static_cast<PowerType>(rand() % 6);
	setPosition(position.x, position.y);
	setRadius(20);
	setOrigin(getRadius(), getRadius());
	//powerupType = mirror;
	switch (powerupType)
	{
	case multiBall:
		powerupTexture.loadFromFile("Textures/multiBall.png");
		setTexture(&powerupTexture);
		break;

	case longerBoard:
		powerupTexture.loadFromFile("Textures/longerBoard.png");
		setTexture(&powerupTexture);
		break;

	case shieldBar:
		powerupTexture.loadFromFile("Textures/shieldBar.png");
		setTexture(&powerupTexture);
		break;

	case stop:
		powerupTexture.loadFromFile("Textures/stop.png");
		setTexture(&powerupTexture);
		break;

	case mirror:
		powerupTexture.loadFromFile("Textures/mirror.png");
		setTexture(&powerupTexture);
		break;

	case lvlup:
		powerupTexture.loadFromFile("Textures/lvlup.png");
		setTexture(&powerupTexture);
		break;
	}
	

}

powerup::powerup(sf::Vector2f position, int type)
{
	powerupType = static_cast<PowerType>(type);
	setPosition(position.x, position.y);
	setRadius(20);
	setOrigin(getRadius(), getRadius());
	switch (powerupType)
	{
	case multiBall:
		powerupTexture.loadFromFile("Textures/multiBall.png");
		setTexture(&powerupTexture);
		break;

	case longerBoard:
		powerupTexture.loadFromFile("Textures/longerBoard.png");
		setTexture(&powerupTexture);
		break;

	case shieldBar:
		powerupTexture.loadFromFile("Textures/shieldBar.png");
		setTexture(&powerupTexture);
		break;

	case stop:
		powerupTexture.loadFromFile("Textures/stop.png");
		setTexture(&powerupTexture);
		break;

	case mirror:
		powerupTexture.loadFromFile("Textures/mirror.png");
		setTexture(&powerupTexture);
		break;

	case lvlup:
		powerupTexture.loadFromFile("Textures/lvlup.png");
		setTexture(&powerupTexture);
	}
	

}

void powerup::update(float dt)
{
	move(0, dt * 40);
}
