#pragma once
#include <SFML/Graphics.hpp>

enum PowerType { multiBall, longerBoard, shieldBar, stop, mirror, lvlup, fuel, maxFuel, explBall, radBall,
	dmgAll, destrRandom, magnet,shorterBoard /*,weapon,setback,magnet*/ };

class powerup : public sf::CircleShape
{

public:

	PowerType powerupType;
	powerup(sf::Vector2f position);
	powerup(sf::Vector2f position,int type);
	
	sf::Texture powerupTexture;
	void update(float dt);
	void update(float dt, bool magnetON, float px, float psize);
	void draw(sf::RenderWindow* w) { w->draw(*this); }
};