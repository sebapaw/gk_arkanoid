#include "powerup.h"
#include <iostream>

using namespace std;

powerup::powerup(sf::Vector2f position)
{
	setPosition(position.x, position.y);
	setRadius(20);
	setOrigin(getRadius(), getRadius());
	setFillColor(sf::Color::Color(255, 0, 0, 125));
	powerupType = static_cast<PowerType>(rand() % 5);
	//powerupType = mirror;
}

powerup::powerup(sf::Vector2f position, int type)
{
	setPosition(position.x, position.y);
	setRadius(20);
	setOrigin(getRadius(), getRadius());
	setFillColor(sf::Color::Color(255, 0, 0, 125));
	powerupType = static_cast<PowerType>(type);

}

void powerup::update(float dt)
{
	move(0, dt * 40);
}
