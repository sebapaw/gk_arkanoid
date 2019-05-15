#pragma once
#include "block.h"
#include "ball.h"
#include <vector>
#include <cmath>
class board
{
	std::vector<block*> blocks;

	sf::RectangleShape border;
	sf::RectangleShape p;
	float psize;


	std::vector<ball*>balls;
	int gamestate;
	float dist(float x1, float y1, float x2, float y2)
	{
		return sqrt((x1 - x2)* (x1 - x2) + (y1 - y2) * (y1 - y2));
	}

	float totaltime = 0;
	float timetomove = 1;

public:

	float pboost = 60;

	int lives = 3;
	int score = 0;

	board();
	void checkghcol();
	void draw(sf::RenderWindow*w);
	void update(float dt);
	void adddefblocks();
	void addrowblocks(int hp);
	void moveblocks();
	bool checkcoli(block* bl, ball* bal);

	~board();
};


