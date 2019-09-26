#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "board.h"
#include "progbar.h"
#include "button.h"

using namespace std;

class interf
{
	sf::RectangleShape* menu, *highscore, * newRecord, *gameover;

	button* startb, *highb, *option0, *gameoverb, *backb;

	sf::RectangleShape infop, infop2;
	
	sf::Text infot2, infot, optiontx, pboosttx, newscoret, newscorenamet, nameunderfield, gameovert, highscorelist;
	sf::Font f;
	board* bd;
	progbar pboost;
	progbar *mirrortime = nullptr, *stoptime = nullptr, *magnettime = nullptr;

	vector<string> hsname;
	vector<int> hsvalue;
	string scoreinput = "";
	int it = 0;
	bool fileread = false;
	bool updscore = true;

	
	void createmenu();
	void createhighscorescreen();
	void creategameoverscreen();
	void createnewRecord();
	void showmenu(sf::RenderWindow*w);
	void showhighscorescreen(sf::RenderWindow*w);
	void showgameoverscreen(sf::RenderWindow*w);
	void shownewRecord(sf::RenderWindow*w);
	void deletemenu() { delete startb; delete highb; delete option0; delete menu; }
	void deletegameoverscreen() { delete gameoverb; }
	void deletehighscorescreen() { delete backb; }
	void deleteendscreen() { delete startb; delete highb; delete option0; delete menu; }
public:
	void draw(sf::RenderWindow*w);

	interf(board*bd);
	~interf();
};

