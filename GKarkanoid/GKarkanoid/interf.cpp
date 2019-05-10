#include "interf.h"
#include <sstream>


void interf::draw(sf::RenderWindow*w)
{
	std::ostringstream ss;
	ss << "lives: " << bd->lives << "\nscore: " << bd->score;

	infot.setString(ss.str());
	w->draw(infop);
	w->draw(infot);
}

interf::interf(board*bd)
{
	this->bd = bd;
	infop.setFillColor(sf::Color::Color(128, 240, 128));
	infop.setSize(sf::Vector2f(165, 300));
	infop.setPosition(1025, 10);
	infop.setOutlineThickness(5);
	infop.setOutlineColor(sf::Color::Color(64, 128, 64));

	if (!f.loadFromFile("sansation.ttf"))
	{
		//err
	}
	infot.setFont(f);
	infot.setCharacterSize(20);
	infot.setPosition(1035, 20);
	infot.setFillColor(sf::Color::Color(0, 0, 255));


}


interf::~interf()
{
}
