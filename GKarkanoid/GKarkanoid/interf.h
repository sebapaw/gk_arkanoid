#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "board.h"
#include "progbar.h"

class interf
{

	sf::RectangleShape infop;
	sf::RectangleShape infop2;

	sf::Text infot;
	sf::Text infot2;
	sf::Font f;
	board* bd;
	progbar pboost;
	

public:
	void draw(sf::RenderWindow*w);



	interf(board*bd);
	~interf();
};

