#pragma once
#include "block.h"
#include "ball.h"
#include "powerup.h"
#include <vector>
#include <cmath>
class board
{
	std::vector<block*> blocks;
	std::vector<powerup*> powerups;
	sf::RectangleShape border;
	sf::RectangleShape p;
	float psize;
	sf::RectangleShape *sBar = nullptr;
	


	std::vector<ball*>balls;
	int gamestate;
	float dist(float x1, float y1, float x2, float y2)
	{
		return sqrt((x1 - x2)* (x1 - x2) + (y1 - y2) * (y1 - y2));
	}

	float totaltime = 0;
	float timetomove = 1;
	bool blockstop = false;
	float stoptime = 5;
	

	
	int dmgmult = 1;
public:

	float pboost = 60;
	int shieldHP = 0;
	float mirrortime = 0;
	float maxmirrortime;
	int lives = 3;
	int score = 0;
	sf::RectangleShape *mirrorP = nullptr;
	

	board();
	void checkghcol();
	void draw(sf::RenderWindow*w);
	void update(float dt);
	void adddefblocks();
	void addrowblocks();
	void moveblocks();
	bool checkcoli(block* bl, ball* bal);

	~board();
};


