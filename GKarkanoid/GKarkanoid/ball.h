#pragma once
#include <SFML/Graphics.hpp>
class ball :public sf::CircleShape
{
	int lvl = 1;
	int basedmg = 1;
public:

	int type;
	void lvlup();
	sf::Vector2f oldpos;
	int getdmg() { return lvl * basedmg; }
	void setangle(float a);
	float getangle();

	void speedup(float s);

	void restart();

	sf::Vector2f v;
	ball(int dmg=1,int t=1);
	void update(float dt);
	void draw(sf::RenderWindow* w) { w->draw(*this); }
	~ball();
};

