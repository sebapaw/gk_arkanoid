#include "block.h"
#include <sstream>




void block::removegh()
{
	isghost = false;
	if (type == 0)
		setFillColor(sf::Color::Color(0, 222, 0));
	else if (type == 1)
	{
		setFillColor(sf::Color::Color(70, 0, 130));
	}
	else if (type == 2)
	{
		setFillColor(sf::Color::Color(128, 0, 0));
	}
	else if (type == 3)
	{
		setFillColor(sf::Color::Color(0, 240, 255));
	}
	
}

block::block(float x, float y, int hp, bool gh,int t)
{
	type = t;
	isghost = gh;
	this->hp = hp;
	maxhp = hp;
	setPosition(x, y);
	setSize(sf::Vector2f(sizex, sizey));
	setOrigin(sizex / 2, sizey / 2);
	if (type == 0)
		setFillColor(sf::Color::Color(0, 222, 0, (gh == false ? 255 : 100)));
	else if (type == 1)
		setFillColor(sf::Color::Color(70, 0, 130, (gh == false ? 255 : 100)));
	else if (type == 2)
		setFillColor(sf::Color::Color(128, 0, 0, (gh == false ? 255 : 100)));
	else if (type == 3)
		setFillColor(sf::Color::Color(0, 240, 255, (gh == false ? 255 : 100)));
	if (!f.loadFromFile("sansation.ttf"))
	{
		//err
		hp += 0;
	}
	hptext.setFont(f);
	hptext.setCharacterSize(18);
	hptext.setFillColor(sf::Color::Color(240, 0, 255));
	if(hp>1000)
		hptext.setPosition(x - 25, y - 11);
	else
		hptext.setPosition(x - 10, y - 11);
	/*std::ostringstream ss;
	ss << hp;
	hptext.setString(ss.str());*/
}

void block::draw(sf::RenderWindow * w,bool opt,int div)
{
	int displayhp = hp;

	if (opt&&type!=2)
		displayhp=ceil(float(hp)/div);

	std::ostringstream ss;
	ss << displayhp;
	hptext.setString(ss.str());
	w->draw(*this);
	w->draw(hptext);
}

bool block::takedmg(int d,int t)
{
	if (t==3)
		rad = pow(pow(d, 1.25) + pow(rad, 1.25), 0.8);
	if (type == 2 && d > 0)
		d = 1;
	else
		d = d*(1+0.02*pow(log(poison+1),1.3));
	if (t == 4)
		poison += d * d;
	hp -= d;
	if (hp < 1)
	{
		return true;
	}
	
	else
	{
		std::ostringstream ss;
		ss << hp;
		hptext.setString(ss.str());
	}
	if (type == 0)
		setFillColor(sf::Color::Color(255 - 255 * hp / maxhp, 222, 0));
	else if (type == 1)
		setFillColor(sf::Color::Color(70, 140 - 140 * hp / maxhp, 130));
	else if (type == 2)
		setFillColor(sf::Color::Color(128, 140 - 140 * hp / maxhp, 0));
	else if (type == 3)
		setFillColor(sf::Color::Color(240 - 240 * hp / maxhp, 240, 255));
	return false;
}

void block::operator--()
{
	move(0, 1);
	hptext.move(0, 1);

	if (type == 3 && rand() % 100 < 60)
	{
		if (maxhp > 80)
		{
			hp += maxhp / (80*(1+0.16*pow(log(poison+1),0.8)));
			if (hp > maxhp)
				hp = maxhp;
		}
		else
			if (rand() % 80 < maxhp&&hp<maxhp&&poison<1)	
				hp++;

		/*std::ostringstream ss;
		ss << hp;
		hptext.setString(ss.str());*/
		setFillColor(sf::Color::Color(240 - 240 * hp / maxhp, 240, 255));
	}

}

void block::upddots(int t)
{
	
	if (t % 2 == 1)
	{
		int raddmg = int((rand() % 100)*(rand() % 100) / 6000.0f * rad);
		takedmg(raddmg);
		rad -= raddmg * 0.12;
	}
	if ((t/ 2)%2 == 1)
	{
		int poisondmg = pow(poison, 0.55)*0.01;
		takedmg(poisondmg);
	}
}

block::~block()
{
}
