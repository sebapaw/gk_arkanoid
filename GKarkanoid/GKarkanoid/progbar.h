#pragma once
#include <SFML/Graphics.hpp>
class progbar
{
	sf::RectangleShape bar, outer;

public:
	void setcolor(int, int, int);
	void setoutercolor(int, int, int);
	void setemptycolor(int, int, int, int a = 255);
	void setsize(float, float);
	void setpos(float, float);
	void operator-=(float);
	void operator+=(float);
	void reset();
	void fill(float p = 100);
	float getfill() { return bar.getSize().x; }

	void show(sf::RenderWindow*w);
	progbar();
	~progbar();
};

