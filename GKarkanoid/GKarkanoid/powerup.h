#pragma once
#include <SFML/Graphics.hpp>

enum PowerType { multiBall, longerBoard, shieldBar, stop, mirror, setback };

class powerup : public sf::CircleShape
{

public:

	PowerType powerupType;
	powerup(sf::Vector2f position);
	sf::Sprite powerupIcon;
	void update(float dt);
	void draw(sf::RenderWindow* w) { w->draw(*this); }
};