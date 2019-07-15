#include "powerup.h"
#include <iostream>

using namespace std;

powerup::powerup(sf::Vector2f position)
{
	powerupType = static_cast<PowerType>(rand() % 13);
	setPosition(position.x, position.y);
	setRadius(20);
	setOrigin(getRadius(), getRadius());
	//powerupType = magnet; /*wiersz testuj¹cy dzia³anie konkretnych powerupów. Domyœlnie zakomentowany*/
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

	case fuel:
		powerupTexture.loadFromFile("Textures/fuel.png");
		setTexture(&powerupTexture);
		break;

	case maxFuel:
		powerupTexture.loadFromFile("Textures/maxFuel.png");
		setTexture(&powerupTexture);
		break;

	case explBall:
		powerupTexture.loadFromFile("Textures/explBall.png");
		setTexture(&powerupTexture);
		break;

	case radBall:
		powerupTexture.loadFromFile("Textures/radBall.png");
		setTexture(&powerupTexture);
		break;

	case dmgAll:
		powerupTexture.loadFromFile("Textures/dmgAll.png");
		setTexture(&powerupTexture);
		break;

	case destrRandom:
		powerupTexture.loadFromFile("Textures/destrRandom.png");
		setTexture(&powerupTexture);
		break;

	case magnet:
		powerupTexture.loadFromFile("Textures/magnet.png");
		setTexture(&powerupTexture);
		break;
	}
	

}

powerup::powerup(sf::Vector2f position, int type)
{
	powerupType = static_cast<PowerType>(type);
	//powerupType = magnet; /*wiersz testuj¹cy dzia³anie konkretnych powerupów. Domyœlnie zakomentowany*/
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
		break;

	case fuel:
		powerupTexture.loadFromFile("Textures/fuel.png");
		setTexture(&powerupTexture);
		break;

	case maxFuel:
		powerupTexture.loadFromFile("Textures/maxFuel.png");
		setTexture(&powerupTexture);
		break;

	case explBall:
		powerupTexture.loadFromFile("Textures/explBall.png");
		setTexture(&powerupTexture);
		break;

	case radBall:
		powerupTexture.loadFromFile("Textures/radBall.png");
		setTexture(&powerupTexture);
		break;

	case dmgAll:
		powerupTexture.loadFromFile("Textures/dmgAll.png");
		setTexture(&powerupTexture);
		break;

	case destrRandom:
		powerupTexture.loadFromFile("Textures/destrRandom.png");
		setTexture(&powerupTexture);
		break;

	case magnet:
		powerupTexture.loadFromFile("Textures/magnet.png");
		setTexture(&powerupTexture);
		break;
	}


	

}

void powerup::update(float dt)
{
	move(0, dt * 40);
}

void powerup::update(float dt, bool magnetON, float px, float psize)
{
	if (magnetON)
	{
		float diff = px - this->getPosition().x + psize/2;
		if (diff > 0)
			move(dt * 60 + diff/100, dt * 40);
		else
			move(-dt * 60 + diff/100, dt * 40);
	}
	else 
	{
		move(0, dt * 40);
	}
	
}
