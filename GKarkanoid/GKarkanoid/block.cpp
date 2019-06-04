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
	else if(type==1)
		setFillColor(sf::Color::Color(70, 0, 130, (gh == false ? 255 : 100)));
	else if (type == 2)
		setFillColor(sf::Color::Color(128, 0, 0, (gh == false ? 255 : 100)));
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
	std::ostringstream ss;
	ss << hp;
	hptext.setString(ss.str());
}

void block::draw(sf::RenderWindow * w)
{
	w->draw(*this);
	w->draw(hptext);
}

bool block::takedmg(int d)
{
	if (type == 2)
		d = 1;
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
	else if(type==1)
		setFillColor(sf::Color::Color(70, 140-140*hp/maxhp, 130));
	else if (type == 2)
		setFillColor(sf::Color::Color(128, 140 - 140 * hp / maxhp, 0));
	return false;
}

void block::operator--()
{
	move(0, 1);
	hptext.move(0, 1);
}

block::~block()
{
}
