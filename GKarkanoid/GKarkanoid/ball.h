#pragma once
#include <SFML/Graphics.hpp>
class ball :public sf::CircleShape
{

public:

	int dmg = 1;
	void setangle(float a);
	float getangle();

	void speedup(float s);

	void restart();

	sf::Vector2f v;
	ball();
	void update(float dt);
	void draw(sf::RenderWindow* w) { w->draw(*this); }
	~ball();
};

