#pragma once
#include <SFML/Graphics.hpp>
class block :public sf::RectangleShape
{
	int hp;
	int maxhp;
	sf::Text hptext;
	sf::Font f;
	const float sizex = 60, sizey = 30;
	
public:
	int type;
	bool isghost;
	
	void removegh();
	block(float x, float y, int hp,bool gh=false, int t=0);

	void draw(sf::RenderWindow* w);
	bool takedmg(int d);
	void operator--();

	~block();
};

