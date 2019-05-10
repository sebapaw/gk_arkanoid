#pragma once
#include <SFML/Graphics.hpp>
class ball :public sf::CircleShape
{

public:

	void setangle(float a);
	float getangle();



	void restart();

	sf::Vector2f v;
	ball();
	void update(float dt);
	void draw(sf::RenderWindow* w) { w->draw(*this); }
	~ball();
};

