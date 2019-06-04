#pragma once
#include <SFML/Graphics.hpp>

enum PowerType { multiBall, longerBoard, shieldBar, stop, mirror, setback };

class powerup : public sf::CircleShape
{

public:

	PowerType powerupType;
	powerup(sf::Vector2f position);
	powerup(sf::Vector2f position,int type);
	sf::Sprite powerupIcon;
	void update(float dt);
	void draw(sf::RenderWindow* w) { w->draw(*this); }
};