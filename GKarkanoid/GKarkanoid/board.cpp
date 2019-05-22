#include "board.h"
#include <cstdlib>


board::board()
{
	border.setPosition(10, 10);
	border.setSize(sf::Vector2f(1000, 750));
	border.setOutlineThickness(5);
	border.setFillColor(sf::Color::Color(40, 40, 40));
	border.setOutlineColor(sf::Color::Color(140, 70, 240));

	p.setFillColor(sf::Color::Color(200, 220, 255));
	psize = 70;
	p.setSize(sf::Vector2f(psize, 10));
	p.setPosition(600, 740);

	balls.push_back(new ball());
	gamestate = 1;

	

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
		blocks[i]->draw(w);
	}
	


}

void board::update(float dt)
{
	if (gamestate == 1)
	{
		if (!blockstop)
		{
			totaltime += dt;
			timetomove -= dt;
		}
		else
		{
			stoptime -= dt;
		}

		mirrortime -= dt;

		if (stoptime < 0)
			blockstop = false;

		if (mirrortime < 0)
		{
			delete mirrorP;
			mirrorP = nullptr;
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
		{
			balls[i]->speedup(dt * 1);
		}


		checkghcol();

		


		for (int j = 0; j < balls.size(); j++)
		{
			balls[j]->update(dt);


			if (sBar)
			{
				float by = balls[j]->getPosition().y;
				
				if (by > 737)
				{
					balls[j]->setPosition(balls[j]->getPosition().x, 1474 - by);
					balls[j]->v.y *= -1;
					shieldHP--;
					if (shieldHP == 0)
					{
						delete sBar;
						sBar = nullptr;
					}
					
				
				}
			}


			for (size_t i = 0; i < blocks.size(); i++)
			{
				if (blocks[i]->isghost == false && checkcoli(blocks[i], balls[j]))
				{

					if (rand() % 20 == 0)
						powerups.push_back(new powerup(blocks[i]->getPosition()));

					if (blocks[i]->takedmg(balls[j]->getdmg()*dmgmult))
					{
						if (blocks[i]->type == 1)
							dmgmult += 1;
						if (rand() % 2 == 0)
							powerups.push_back(new powerup(blocks[i]->getPosition()));
						delete blocks[i];
						blocks.erase(blocks.begin() + i);


						score += 1;
					}
				}
			}


			float bx = balls[j]->getPosition().x;
			float by = balls[j]->getPosition().y;

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
			if (by > 732) {

				if (bx > px&&bx < px + psize && by < 740)
				{
					balls[j]->setPosition(bx, 1464 - by);
					balls[j]->v.y *= -1;
					float angchange = ((bx - px) / psize - 0.5) * 100;
					float ang = balls[j]->getangle() + angchange;

					if (ang > 320)ang = 320 + 40 * ((ang - 320) / (ang - 280));
					if (ang < 220)ang = 220 - ((220 - ang) / (260 - ang) * 40);
					balls[j]->setangle(ang);

					//moveblocks();
				}

				if (mirrorP)
				{
					float mpx = mirrorP->getPosition().x;

					if (bx > mpx&&bx < mpx + psize && by < 740)
					{
						balls[j]->setPosition(bx, 1464 - by);
						balls[j]->v.y *= -1;
						float angchange = ((bx - mpx) / psize - 0.5) * 100;
						float ang = balls[j]->getangle() + angchange;

						if (ang > 320)ang = 320 + 40 * ((ang - 320) / (ang - 280));
						if (ang < 220)ang = 220 - ((220 - ang) / (260 - ang) * 40);
						balls[j]->setangle(ang);

						//moveblocks();
					}
				}
				if (by > 740)
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

		for (int i = 0; i < powerups.size();i++)
		{
			powerups[i]->update(dt);
			float px = p.getPosition().x;
			float pux = powerups[i]->getPosition().x;
			float puy = powerups[i]->getPosition().y;

			if (puy > 740 - powerups[i]->getRadius())
			{
				if (pux > px&&pux < px + psize && puy < 740)
				{

					switch (powerups[i]->powerupType)
					{
					case multiBall:
						balls.push_back(new ball());
						delete powerups[i];
						powerups.erase(powerups.begin() + i);
						break;

					case longerBoard:
						psize += 10;
						p.setSize(sf::Vector2f(psize, 10));
						delete powerups[i];
						powerups.erase(powerups.begin() + i);
						break;

					case shieldBar:
						sBar = new sf::RectangleShape();
						sBar->setSize(sf::Vector2f(1000, 5));
						sBar->setPosition(10, 745);
						shieldHP += 2;
						sBar->setFillColor(sf::Color::Color(0, 0, 255));
						delete powerups[i];
						powerups.erase(powerups.begin() + i);
						break;

					case stop:
						blockstop = true;
						stoptime += 5;
						delete powerups[i];
						powerups.erase(powerups.begin() + i);
						break;


					case mirror:
						delete mirrorP;
						mirrorP = new sf::RectangleShape();
						float oldmirrortime = mirrortime;
						mirrortime = (rand() % 20) + 10;
						mirrortime = sqrt(pow(mirrortime,2) + pow(oldmirrortime,2));
						maxmirrortime = mirrortime;

						mirrorP->setSize(sf::Vector2f(psize, 10));
						mirrorP->setPosition(1010 - p.getPosition().x - psize, p.getPosition().y);
						mirrorP->setFillColor(sf::Color::Color(225, 225, 225, 128));
						delete powerups[i];
						powerups.erase(powerups.begin() + i);
						break;
					}

					

				}
				if (puy > 740)
				{
					delete powerups[i];
					powerups.erase(powerups.begin() + i);
				}
			}
		}

		

			pboost += dt * 4;
			if (pboost > 120) pboost = 120;

			float pspeed = 190;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && pboost > dt * 15)
			{
				pboost -= dt * 15;
				pspeed *= 3;
			}
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
			if (p.getPosition().x > 1010-psize)p.setPosition(1010-psize, p.getPosition().y);

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
		else if(rand()%10>1)
		blocks.push_back(new block(200 + 65 * j, 100, newhp,true));
	}
	rows++;
}

void board::moveblocks()
{
	for (size_t i = 0; i < blocks.size(); i++)	//obnizanie klockow
	{
		--*blocks[i];
		if (blocks[i]->getPosition().y > 725)
			gamestate = 99;
	}
}

bool board::checkcoli(block * bl, ball* bal)
{
	bool ng = !bl->isghost;

	float r = bal->getRadius();
	float xa = bal->getPosition().x;
	float ya = bal->getPosition().y;

	float xleft = bl->getPosition().x - (bl->getSize().x / 2);
	float xright = bl->getPosition().x + (bl->getSize().x / 2);
	float ytop = bl->getPosition().y - (bl->getSize().y / 2);
	float ydown = bl->getPosition().y + (bl->getSize().y / 2);

	if (xa + r > xleft && xa - r < xright && ya > ytop && ya < ydown)
	{
		if(ng)bal->v.x *= -1;
		return true;
	}
	else if (ya + r > ytop && ya - r<ydown && xa>xleft && xa < xright)
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

board::~board()
{
}
