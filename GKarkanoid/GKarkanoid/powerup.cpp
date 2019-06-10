#include "powerup.h"
#include <iostream>

using namespace std;

powerup::powerup(sf::Vector2f position)
{
	powerupType = static_cast<PowerType>(rand() % 6);
	setPosition(position.x, position.y);
	setRadius(20);
	setOrigin(getRadius(), getRadius());
	if (powerupType == lvlup)
		setFillColor(sf::Color::Color(0, 125, 255, 125));
	else
		setFillColor(sf::Color::Color(255, 0, 0, 125));
	
	//powerupType = mirror;
}

powerup::powerup(sf::Vector2f position, int type)
{
	powerupType = static_cast<PowerType>(type);
	setPosition(position.x, position.y);
	setRadius(20);
	setOrigin(getRadius(), getRadius());
	if (powerupType == lvlup)
		setFillColor(sf::Color::Color(0, 125, 255, 125));
	else
		setFillColor(sf::Color::Color(255, 0, 0, 125));
}

void powerup::update(float dt)
{
	move(0, dt * 40);
}
