#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "board.h"

class interf
{

	sf::RectangleShape infop;
	sf::Text infot;
	sf::Font f;
	board* bd;

public:
	void draw(sf::RenderWindow*w);



	interf(board*bd);
	~interf();
};

