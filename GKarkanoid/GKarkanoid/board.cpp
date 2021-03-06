#include "board.h"
#include <cstdlib>


void board::updpowerups(float dt)
{
	for (int i = 0; i < powerups.size(); i++)
	{
		float px = p.getPosition().x;
		powerups[i]->update(dt, magnetON,px,psize);
		float pux = powerups[i]->getPosition().x;
		float puy = powerups[i]->getPosition().y;

		if (puy > 730 - powerups[i]->getRadius())
		{
			if (pux > px&&pux < px + psize && puy < 740)
			{
				switch (powerups[i]->powerupType)
				{
				case multiBall:
					balls.push_back(new ball());
					break;

				case longerBoard:
					if (psize < 120)
						psize += 8;
					else if (psize < 240)
						psize += 4;
					else if (psize < 320)
						psize += 2;
					else if (psize < 380)
						psize += 1;
					else
						psize += (10 / (psize - 360));
					p.setSize(sf::Vector2f(psize, 10));
					if (mirrorP) mirrorP->setSize(sf::Vector2f(psize, 10));
					break;

				case shieldBar:
					sBar = new sf::RectangleShape();
					sBar->setSize(sf::Vector2f(1000, 5));
					sBar->setPosition(10, 735);
					shieldHP += ((shieldHP>200?1:2) + rand() % 2)*shieldmult;
					sBar->setFillColor(sf::Color::Color(0, 0, 255));
					break;

				case stop:
					blockstop = true;
					if (stoptime < 10)
						stoptime += 5;
					else
						stoptime += (10 / (1 + stoptime)) * 5;
					maxstoptime = stoptime;
					break;
				case mirror:
					delete mirrorP;
					mirrorP = new sf::RectangleShape();
					//float oldmirrortime = mirrortime;
					//mirrortime = (rand() % 20) + 10;
					mirrortime = sqrt(pow(mirrortime, 2) + pow((rand() % 20) + 10, 2));
					maxmirrortime = mirrortime;

					mirrorP->setSize(sf::Vector2f(psize, 10));
					mirrorP->setPosition(1010 - p.getPosition().x - psize, p.getPosition().y);
					mirrorP->setFillColor(sf::Color::Color(210, 225, 240, 128));
					break;

				case lvlup:
					balls[rand() % balls.size()]->lvlup();
					break;

				case fuel:
					pboost += 10;
					break;

				case maxFuel:
					if (maxfuel < 300)
						maxfuel += 15;
					else
						maxfuel += 10;
					break;

				case explBall:
					balls[rand() % balls.size()]->updtype(2);
					break;

				case radBall:
					balls[rand() % balls.size()]->updtype(3);
					break;

				case dmgAll:
					for (int ii = 0; ii < blocks.size(); ii++)
					{
						if (blocks[ii]->takedmg(dmgmult))
						{
							removeblock(ii);
							ii--;
						}
					}
					break;

				case magnet:
					magnetON = true;
					p.setFillColor(sf::Color::Color(220,60,120));
					if (magnettime < 0)
						magnettime = 0;
					if (magnettime < 10)
						magnettime += 10;
					else
						magnettime += (40 / ( magnettime-6));
					maxmagnettime = magnettime;
					break;

				case destrRandom:
					if(blocks.size()>0)
						removeblock(rand() % blocks.size());
					break;
				case shorterBoard:
					psize -= 1;
					p.setSize(sf::Vector2f(psize, 10));
					if (mirrorP) mirrorP->setSize(sf::Vector2f(psize, 10));
				case poisonBall:
					balls[rand() % balls.size()]->updtype(4);
					break;
				}

				delete powerups[i];
				powerups.erase(powerups.begin() + i);

			}
			if (puy > 730)
			{
				delete powerups[i];
				powerups.erase(powerups.begin() + i);
			}
		}
	}
}

void board::findlowestblock()
{
	float lowest = 0;
	for (int i = 0; i < blocks.size(); i++)
	{
		if (blocks[i]->getPosition().y > lowest)
			lowest = blocks[i]->getPosition().y;
	}
	lowestblockpos = lowest + 23;
}

void board::bexplode(sf::Vector2f pos , int dmg)
{
	float radius = 85+6*log(dmg);
	for (int i = 0; i <blocks.size(); i++)
	{
		float d = dist(pos.x, pos.y, blocks[i]->getPosition().x, blocks[i]->getPosition().y);
		if (d < radius)
		{
			dmg = (1 - d / radius)*dmg*0.6*dmgmult;
			if (dmg < 1) dmg = 1;
			if (blocks[i]->takedmg(dmg))
			{
				removeblock(i);
				i--;
			}
		}
	}
}

void board::removeblock(int i)
{
	int t = blocks[i]->type;
	
	if (blocks[i]->type == 1)
		dmgmult += 1;
	else if (blocks[i]->type == 2)
		shieldmult += 1;
	if (rand() % 5 <2)
		powerups.push_back(new powerup(blocks[i]->getPosition(), rollb(bonuschances)));
	score += 1;
	delete blocks[i];
	blocks.erase(blocks.begin() + i);
	findlowestblock();
}

void board::bounce(ball * bal,float px)
{
	bal->setPosition(bal->getPosition().x, 1444 - bal->getPosition().y);
	bal->v.y *= -1;
	if (px > -0.5)
	{
		float angchange = ((bal->getPosition().x - px) / psize - 0.5) * 100;
		float ang = bal->getangle() + angchange;

		if (ang > 320)ang = 320 + 40 * ((ang - 320) / (ang - 280));
		if (ang < 220)ang = 220 - ((220 - ang) / (260 - ang) * 40);
		bal->setangle(ang);
	}
}

board::board()
{
	border.setPosition(10, 10);
	border.setSize(sf::Vector2f(1000, 740));
	border.setOutlineThickness(5);
	border.setFillColor(sf::Color::Color(40, 40, 40));
	border.setOutlineColor(sf::Color::Color(140, 70, 240));

	p.setFillColor(sf::Color::Color(200, 220, 255));
	psize = 70;
	p.setSize(sf::Vector2f(psize, 10));
	p.setPosition(600, 730);

	balls.push_back(new ball());
	gamestate = 0;
	adddefblocks();
	findlowestblock();
	

}

void board::checkghcol()
{
	for (size_t i = 0; i < blocks.size(); i++)
	{
		if (blocks[i]->isghost)
		{
			bool nocoli = true;
			for (int j = 0; j < balls.size(); j++)
			{
				if (checkcoli(blocks[i], balls[j]))
					nocoli = false;
			}
			if (nocoli)
				blocks[i]->removegh();
		}
	}

}

void board::draw(sf::RenderWindow * w)
{

	w->draw(border);
	if (sBar)
		w->draw(*sBar);
	if (mirrorP)
		w->draw(*mirrorP);
	w->draw(p);
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->draw(w);
	}
	for (int i = 0; i < powerups.size(); i++)
	{
		powerups[i]->draw(w);
	}
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->draw(w,option0,dmgmult);
	}
	

}

void board::update(float dt)
{
	if (gamestate == 1)
	{
		scoresaved = false;
		int dotst = 0;// rad=1, poison=2,...=4,..
		for (int i = 0; i < 2; i++)
		{
			dottimer[i] -= dt;
			if (dottimer[i] < 0)
			{
				dottimer[i] += 1;	//rad - 1s, poison - 1s,
				dotst += pow(2, i);
			}
		}
		if (dotst > 0)
			for (int i = 0; i < blocks.size(); i++)
			{
				blocks[i]->upddots(dotst);
				if (blocks[i]->gethp() < 1)
					removeblock(i);
			}
			
		bool downpress = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		if (!blockstop|| downpress)
		{
			if (downpress)
			{
				totaltime += dt*20;
				timetomove -= dt*20;
			}
			else
			{
				totaltime += dt;
				timetomove -= dt;
			}
		}
		else
			stoptime -= dt;
		//todo highscore zapisywanie
		mirrortime -= dt;
		magnettime -= dt;

		if (stoptime < 0)
			blockstop = false;

		if (mirrortime < 0)
		{
			delete mirrorP;
			mirrorP = nullptr;
		}

		if (magnettime < 0)
		{
			magnetON = false;
			p.setFillColor(sf::Color::Color(200, 220, 255));
		}
			
		if (timetomove < 0)
		{
			moveblocks();
			timetomove += 1;
		}
		static int level = 1;
		if (totaltime > 35 * level)
		{
			addrowblocks();
			level++;
		}

		for (size_t i = 0; i < balls.size(); i++)
			balls[i]->speedup(dt * 1);

		checkghcol();

		for (int j = 0; j < balls.size(); j++)
		{
			balls[j]->update(dt);
			float bx = balls[j]->getPosition().x;
			float by = balls[j]->getPosition().y;
			if(!(by>lowestblockpos||by<77))//optymalizacja
				for (size_t i = 0; i < blocks.size(); i++)
				{
					if (blocks[i]->isghost == false && checkcoli(blocks[i], balls[j]))
					{
						int chance = 50 - floor(10*log((double)(balls.size())));
						if (rand() % 1000<chance)
							powerups.push_back(new powerup(blocks[i]->getPosition(),rollb(bonuschances2)));

						if (blocks[i]->takedmg(balls[j]->getdmg()*dmgmult,balls[j]->type))
							removeblock(i);

						if (balls[j]->type == 2)
							bexplode(balls[j]->getPosition(), balls[j]->getdmg());
					}
				}

			float px = p.getPosition().x;

			if (bx > 1002) {
				balls[j]->setPosition(2004 - bx, by);
				balls[j]->v.x *= -1;
			}
			if (bx < 18) {
				balls[j]->setPosition(36 - bx, by);
				balls[j]->v.x *= -1;
			}
			if (by < 18) {
				balls[j]->setPosition(bx, 36 - by);
				balls[j]->v.y *= -1;
			}
			if (by > 722) {
					
				if (bx > px&&bx < px + psize && (by < 740 || balls[j]->oldpos.y < 722) && balls[j]->v.y>0)
					bounce(balls[j],px);

				

				if (mirrorP)
				{
					float mpx = mirrorP->getPosition().x;

					if (bx > mpx&&bx < mpx + psize && (by < 740 || balls[j]->oldpos.y < 722) && balls[j]->v.y>0)
						bounce(balls[j], mpx);
				}

				if (sBar)
				{
					float by = balls[j]->getPosition().y;
					if (by > 727 && balls[j]->v.y > 0)
					{
						bounce(balls[j]);
						shieldHP -= balls[j]->getdmg();
						if (shieldHP < 1)
						{
							delete sBar;
							sBar = nullptr;
							shieldHP = 0;
						}
					}
				}
				if (by > 738)
				{
					if (balls.size() > 1)
					{
						delete balls[j];
						balls.erase(balls.begin() + j);
					}
					else
					{
						lives--;

						if (lives < 0)
						{
							gamestate = 99;
							return;
						}
						balls[0]->restart();
					}
				}
			}
		}

		updpowerups(dt);

		pboost += dt * 4;
		if (pboost > maxfuel) pboost = maxfuel;

		float pspeed = 240;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && pboost > dt * 15)
		{
			pboost -= dt * 15;
			pspeed *= 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			pspeed *= 0.5;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			p.move(-pspeed * dt, 0);
			if (mirrorP)
				mirrorP->move(pspeed * dt, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			p.move(pspeed * dt, 0);
			if (mirrorP)
				mirrorP->move(-pspeed * dt, 0);
		}

		if (p.getPosition().x < 10)p.setPosition(10, p.getPosition().y);
		if (p.getPosition().x > 1010 - psize)p.setPosition(1010 - psize, p.getPosition().y);

		if (mirrorP)
		{
			if (mirrorP->getPosition().x < 10)mirrorP->setPosition(10, mirrorP->getPosition().y);
			if (mirrorP->getPosition().x > 1010 - psize)mirrorP->setPosition(1010 - psize, mirrorP->getPosition().y);
		}


	}
	
}

void board::adddefblocks()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			blocks.push_back(new block(200 + 65 * i, 100 + 35 * j, (j>6?1:2)));
		}
	}
}

void board::addrowblocks()
{
	static int rows = 1;
	int newhp = floor(pow(2, pow(rows, 0.5)));
	int rndpos = rand() % 10;
	for (int j = 0; j < 10; j++)
	{
		if (j == rndpos && rows % 5 == 0)
		{
			blocks.push_back(new block(200 + 65 * j, 100, newhp*3, true,1));
		}
		else if (j==(rndpos+5)%10&&floor(sqrt(rows+1))==sqrt(rows+1))
		{
			blocks.push_back(new block(200 + 65 * j, 100, floor(pow(2, pow(rows, 0.42))) , true, 2));
		}
		else
		{
			int r = rand() % 10;
			if ( r> 2)
				blocks.push_back(new block(200 + 65 * j, 100, newhp, true));
			if (r == 2)
				blocks.push_back(new block(200 + 65 * j, 100, ceil(newhp*1.4), true, 3));
		}
	}
	rows++;

	findlowestblock();

}

void board::moveblocks()
{
	for (size_t i = 0; i < blocks.size(); i++)	//obnizanie klockow
		--*blocks[i];
	

	lowestblockpos += 1;
	if (lowestblockpos>738)
		gamestate = 99;
	for (size_t i = 0; i < balls.size(); i++)
		balls[i]->move(0, 1);
	

	if (rand() % 100 < 7)
	{
		int multballch = floor(450 * pow(0.84, balls.size()));
		bonuschances3[0] = multballch;
			powerups.push_back(new powerup(sf::Vector2f(rand() % 980 + 20, 20), rollb(bonuschances3)));
	}

}

bool board::checkcoli(block * bl, ball* bal)
{

	float r = bal->getRadius();
	float xa = bal->getPosition().x;
	float ya = bal->getPosition().y;
	

	float xleft = bl->getPosition().x - (bl->getSize().x / 2);
	float xright = bl->getPosition().x + (bl->getSize().x / 2);
	float ytop = bl->getPosition().y - (bl->getSize().y / 2);
	float ydown = bl->getPosition().y + (bl->getSize().y / 2);

	if (xa > xright + r || xa < xleft - r || ya + r<ytop || ya - r>ydown)	//optymalizacja
	{
		return false;
	}

	bool ng = !bl->isghost;

	sf::Vector2f curbal(xa, ya);
	//sf::Vector2f blLT(xleft, ytop);
	//sf::Vector2f blLD(xleft, ydown);
	//sf::Vector2f blRT(xright, ytop);
	//sf::Vector2f blRD(xright, ydown);


	if (xa + r > xleft && xa - r < xright && ya > ytop && ya < ydown) // left & right
	{
		if (xa < xleft && bal->oldpos.x < xa)
		{
			if (ng)bal->v.x *= -1;
			return true;
		}
		if (xa > xright && bal->oldpos.x > xa)
		{
			if (ng)bal->v.x *= -1;
			return true;
		}
		

		sf::Vector2f blLT(xleft, ytop);
		sf::Vector2f blLD(xleft, ydown);
		sf::Vector2f blRT(xright, ytop);
		sf::Vector2f blRD(xright, ydown);

		if (isIntersecting(curbal, bal->oldpos, blLT - sf::Vector2f(-8, 0), blLD) && ng) //left wall
		{
			int x = 0;
			if (ng)bal->v.x *= -1;
			return true;
		}
		else if (isIntersecting(curbal, bal->oldpos, blRT, blRD) && ng) //right wall
		{
			int x = 0;
			if (ng)bal->v.x *= -1;
			return true;
		}
		else if (isIntersecting(curbal, bal->oldpos, blLT, blRT) && ng) //top wall
		{
			int x = 0;
			if (ng)bal->v.y *= -1;
			return true;
		}
		else if (isIntersecting(curbal, bal->oldpos, blLD, blRD) && ng) //down wall
		{
			int x = 0;
			if (ng)bal->v.y *= -1;
			return true;
		}
		
	}
	else if (ya + r > ytop && ya - r<ydown && xa>xleft && xa < xright) // top & down
	{
		if (ng)bal->v.y *= -1;
		return true;
	}
	else if (dist(xa, ya, xleft, ytop) < r)
	{
		//bal->v = sf::Vector2f(-2, -2);
		if (ng)bal->setangle(225);
		return true;
	}
	else if (dist(xa, ya, xleft, ydown) < r)
	{
		//bal->v = sf::Vector2f(-2, 2);
		if (ng)bal->setangle(135);
		return true;
	}
	else if (dist(xa, ya, xright, ytop) < r)
	{
		//bal->v = sf::Vector2f(2, -2);
		if (ng)bal->setangle(315);
		return true;
	}
	else if (dist(xa, ya, xright, ydown) < r)
	{
		//bal->v = sf::Vector2f(2, 2);
		if (ng)bal->setangle(45);
		return true;
	}

	return false;
}

bool board::isIntersecting(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2)
{
	return (((q1.x - p1.x)*(p2.y - p1.y) - (q1.y - p1.y)*(p2.x - p1.x))
		* ((q2.x - p1.x)*(p2.y - p1.y) - (q2.y - p1.y)*(p2.x - p1.x)) < 0)
		&&
		(((p1.x - q1.x)*(q2.y - q1.y) - (p1.y - q1.y)*(q2.x - q1.x))
			* ((p2.x - q1.x)*(q2.y - q1.y) - (p2.y - q1.y)*(q2.x - q1.x)) < 0);
}

board::~board()
{
}
