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
	w->draw(p);
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->draw(w);
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
		totaltime += dt;
		timetomove -= dt;
		if (timetomove < 0)
		{
			moveblocks();
			timetomove += 1;
		}
		static int level = 1;
		if (totaltime > 35 * level)
		{
			addrowblocks(3 + level);
			level++;
		}

		for (size_t i = 0; i <balls.size(); i++)
		{
			balls[i]->speedup(dt * 1);
		}
		

		checkghcol();
		for (int j = 0; j < balls.size(); j++)
		{
			balls[j]->update(dt);


			for (size_t i = 0; i < blocks.size(); i++)
			{
				if (blocks[i]->isghost == false && checkcoli(blocks[i], balls[j]) )
				{
					
						if (blocks[i]->takedmg(1))
						{
							delete blocks[i];
							blocks.erase(blocks.begin() + i);
							if (rand() % 2 == 0)
								balls.push_back(new ball());
							score += 1;
						}

						if (rand() % 10 == 0)
							balls.push_back(new ball());
					
					
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
				else if (by > 740)
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

		pboost += dt * 4;
		if (pboost > 120) pboost = 120;

		float pspeed = 190;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && pboost > dt * 15)
		{
			pboost -= dt * 15;	
			pspeed *= 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			p.move(-pspeed * dt, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			p.move(pspeed * dt, 0);
		if (p.getPosition().x < 10)p.setPosition(10, p.getPosition().y);
		if (p.getPosition().x > 940)p.setPosition(940, p.getPosition().y);


	}
}


void board::adddefblocks()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			blocks.push_back(new block(200 + 65 * i, 100 + 35 * j, 2));
		}
	}
}

void board::addrowblocks(int hp)
{
	for (int j = 0; j < 10; j++)
	{
		blocks.push_back(new block(200 + 65 * j, 100, hp,true));
	}
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
