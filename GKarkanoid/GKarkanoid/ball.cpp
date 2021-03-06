#include "ball.h"



void ball::lvlup()
{
	lvl++;
	if (lvl == 2)setFillColor(sf::Color::Color(55, 255, 255));
	if (lvl == 3)setFillColor(sf::Color::Color(255, 55, 255));
	if (lvl == 4)setFillColor(sf::Color::Color(155, 55, 255));
	if (lvl == 5)setFillColor(sf::Color::Color(255, 155, 55));
	if (lvl == 6)setFillColor(sf::Color::Color(55, 155, 255));
	if (lvl == 7)setFillColor(sf::Color::Color(55, 255, 155));
	if (lvl == 8)setFillColor(sf::Color::Color(255, 55, 155));
	if (lvl == 9)setFillColor(sf::Color::Color(155, 255, 55));
	if (lvl == 10)setFillColor(sf::Color::Color(155, 155, 155));
	if (lvl == 11)setFillColor(sf::Color::Color(255, 255, 155));
	if (lvl == 12)setFillColor(sf::Color::Color(155, 255, 255));
	if (lvl == 13)setFillColor(sf::Color::Color(255, 155, 255));
	if (lvl == 14)setFillColor(sf::Color::Color(255, 155, 155));
	if (lvl == 15)setFillColor(sf::Color::Color(155, 255, 155));
	if (lvl == 16)setFillColor(sf::Color::Color(155, 155, 255));
	if (lvl == 17)setFillColor(sf::Color::Color(255, 55, 55));
	if (lvl == 18)setFillColor(sf::Color::Color(55, 255, 55));
	if (lvl == 19)setFillColor(sf::Color::Color(55, 55, 255));
	if (lvl == 20)setFillColor(sf::Color::Color(255, 255, 255));
}

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

void ball::speedup(float s)
{
	float tmp = sqrt(v.x*v.x + v.y*v.y);
	tmp += s;

	float a = getangle();
	const float r = 57.2957795;
	v.x = cos(a / r)*tmp;
	v.y = sin(a / r)*tmp;


}

void ball::restart()
{
	setPosition(900, 600);
	v = sf::Vector2f(90, -60);
}

ball::ball(int dmg, int t)
{
	type = t;
	basedmg = dmg;
	setPosition(900, 600);
	setFillColor(sf::Color::Color(255, 255, 55));
	setRadius(8);
	setOrigin(getRadius(), getRadius());
	v = sf::Vector2f(90, -60);

	if (type == 2)
	{
		setOutlineThickness(4);
		setOutlineColor(sf::Color::Color(220, 150, 0,150));
	}
	if (type == 3)
	{
		setOutlineThickness(4);
		setOutlineColor(sf::Color::Color(150, 245, 180,150));
	}
	if (type == 4)
	{
		setOutlineThickness(4);
		setOutlineColor(sf::Color::Color(40,160, 0, 170));
	}

}

void ball::update(float dt)
{
	oldpos = getPosition();
	if (type == 2)
	{
		move(v*dt*0.7f);
		if (rand() % 20 == 0)
			setOutlineColor(sf::Color::Color(200 + rand() % 56, 50 + rand() % 150, rand() % 100, 110 + rand() % 55));
	}
	else
		move(v*dt);

	float speed = sqrt(v.x*v.x + v.y*v.y);
	if (speed > 275+25*sqrt(lvl))
	{
		float a = getangle();
		const float r = 57.2957795;
		v.x = cos(a / r) * 120;
		v.y = sin(a / r) * 120;

		lvlup();
	}
}


ball::~ball()
{
}
