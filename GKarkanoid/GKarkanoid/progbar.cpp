#include "progbar.h"



void progbar::setcolor(int r, int g, int b)
{
	bar.setFillColor(sf::Color::Color(r, g, b));
}

void progbar::setoutercolor(int r, int g, int b)
{
	outer.setOutlineColor(sf::Color::Color(r, g, b));
}

void progbar::setemptycolor(int r, int g, int b, int a)
{
	outer.setFillColor(sf::Color::Color(r, g, b, a));
}

void progbar::setsize(float s, float h)
{
	outer.setSize(sf::Vector2f(s, h));
	bar.setSize(sf::Vector2f(bar.getSize().x, h));
}

void progbar::setpos(float x, float y)
{
	bar.setPosition(x, y);
	outer.setPosition(x, y);
}

void progbar::operator-=(float v)
{
	float a = bar.getSize().x - v;
	if (a < 0)
		a = 0;
	bar.setSize(sf::Vector2f(a, bar.getSize().y));
}
void progbar::operator+=(float v)
{
	float a = bar.getSize().x + v;
	if (a> outer.getSize().x)
		a = outer.getSize().x;
	bar.setSize(sf::Vector2f(a, bar.getSize().y));
}

void progbar::reset()
{
	fill(0);
}

void progbar::fill(float p)
{
	if (p < 0)p = 0;
	if (p > 100)p = 100;
	float a = (outer.getSize().x / 100.0f)*p;

	bar.setSize(sf::Vector2f(a, bar.getSize().y));
}

void progbar::show(sf::RenderWindow * w)
{
	w->draw(outer);
	w->draw(bar);
}

progbar::progbar()
{
	outer.setOutlineThickness(1);
	outer.setFillColor(sf::Color::Color(0, 0, 0, 0));
	bar.setSize(sf::Vector2f(100, 30));
	setoutercolor(255, 0, 0);

}


progbar::~progbar()
{
}
