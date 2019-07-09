#pragma once
#include <SFML/Graphics.hpp>
class ball :public sf::CircleShape
{
	int lvl = 1;
	int basedmg = 1;
public:

	int type;
	void lvlup();
	void updtype(int t)
	{
		type = t;
		if (type == 2)
		{
			setOutlineThickness(4);
			setOutlineColor(sf::Color::Color(220, 150, 0, 150));
		}
		if (type == 3)
		{
			setOutlineThickness(4);
			setOutlineColor(sf::Color::Color(150, 245, 180, 150));
		}
	}
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

