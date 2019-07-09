#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "board.h"
#include "progbar.h"
#include "button.h"

class interf
{
	sf::RectangleShape* menu;

	button* startb, *highb, *option0;

	sf::RectangleShape infop, infop2;
	
	sf::Text infot2, infot, optiontx, pboosttx;
	sf::Font f;
	board* bd;
	progbar pboost;
	progbar *mirrortime = nullptr, *stoptime = nullptr;
	
	void createmenu();
	void showmenu(sf::RenderWindow*w);
	void deletemenu() { delete startb; delete highb; delete option0; delete menu; }
public:
	void draw(sf::RenderWindow*w);

	interf(board*bd);
	~interf();
};

