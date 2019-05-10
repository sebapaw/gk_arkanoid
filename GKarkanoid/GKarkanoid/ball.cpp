#include "ball.h"



void ball::setangle(float a)
{
	float speed = sqrt(v.x*v.x + v.y*v.y);
	const float r = 57.2957795;

	v.x = cos(a / r)*speed;
	v.y = sin(a / r)*speed;
}

float ball::getangle()
{
	const float r = 57.2957795;
	float speed = sqrt(v.x*v.x + v.y*v.y);
	float ang = r * acos(v.x / speed);
	if (v.y < 0)
		ang = 360 - ang;
	return ang;
}

void ball::restart()
{
	setPosition(900, 600);
	v = sf::Vector2f(90, -60);
}

ball::ball()
{
	setPosition(900, 600);
	setFillColor(sf::Color::Color(255, 255, 55));
	setRadius(8);
	setOrigin(getRadius(), getRadius());
	v = sf::Vector2f(90, -60);

}

void ball::update(float dt)
{
	move(v*dt);
}


ball::~ball()
{
}
