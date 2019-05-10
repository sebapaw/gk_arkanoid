#include "block.h"
#include <sstream>




block::block(float x, float y, int hp)
{
	this->hp = hp;
	maxhp = hp;
	setPosition(x, y);
	setSize(sf::Vector2f(sizex, sizey));
	setOrigin(sizex / 2, sizey / 2);
	setFillColor(sf::Color::Color(0, 222, 0));
	if (!f.loadFromFile("sansation.ttf"))
	{
		//err
		hp += 0;
	}
	hptext.setFont(f);
	hptext.setCharacterSize(20);
	hptext.setFillColor(sf::Color::Color(240, 0, 255));
	hptext.setPosition(x - 10, y - 10);
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
	setFillColor(sf::Color::Color(255 - 255 * hp / maxhp, 222, 0));
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
