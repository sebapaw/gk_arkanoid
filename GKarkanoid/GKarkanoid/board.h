#pragma once
#include "block.h"
#include "ball.h"
#include "powerup.h"
#include <vector>
#include <cmath>
class board
{
	std::vector<ball*>balls;
	std::vector<block*> blocks;
	std::vector<powerup*> powerups;
	sf::RectangleShape border, p, *sBar = nullptr;
	
	
	float dist(float x1, float y1, float x2, float y2)
	{
		return sqrt((x1 - x2)* (x1 - x2) + (y1 - y2) * (y1 - y2));
	}

	float totaltime = 0, timetomove = 1;

	const static int bonustypes=11;
	int bonuschances[bonustypes] = { 150,200,200,200,70,80,20,20,20,20,20 };
	int bonuschances2[bonustypes] = { 150,200,300,200,70,80 };
	int bonuschances3[bonustypes] = { 150,200,300,200,70,80 };
	int rollb(int ch[])
	{
		int a = rand() % 1000;
		for (size_t i = 0; i < bonustypes; i++)
		{
			if (a < ch[i])
				return i;
			else
				a -= ch[i];
		}
		return -1;	//err
	}


	void updpowerups(float dt);
	
		
	void findlowestblock();		//lowestpos +23
	float lowestblockpos;

	void bexplode(sf::Vector2f pos, int dmg);

	void removeblock(int i);
public:
	bool option0 = false;

	bool blockstop = false;
	float stoptime = 5, maxstoptime;
	int gamestate;
	int getballc() { return balls.size(); }
	float psize;
	int shieldmult = 1;
	int dmgmult = 1;
	float pboost = 60, maxfuel = 120;
	int shieldHP = 0;
	float mirrortime = 0, maxmirrortime;
	
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

	bool isIntersecting(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2);

	~board();
};


