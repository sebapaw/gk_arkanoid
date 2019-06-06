#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "board.h"
#include "progbar.h"
#include "button.h"

class interf
{
	sf::RectangleShape* menu;

	button* startb, *highb;

	sf::RectangleShape infop;
	sf::RectangleShape infop2;

	sf::Text infot;
	sf::Text infot2;
	sf::Font f;
	board* bd;
	progbar pboost;
	progbar *mirrortime = nullptr;
	
	void createmenu();
	void showmenu(sf::RenderWindow*w);
	void deletemenu() { delete startb; delete highb; delete menu; }
public:
	void draw(sf::RenderWindow*w);



	interf(board*bd);
	~interf();
};

