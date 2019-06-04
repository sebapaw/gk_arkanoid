#include "interf.h"
#include <sstream>


void interf::draw(sf::RenderWindow*w)
{
	if (!mirrortime&&bd->mirrorP)
	{
		mirrortime = new progbar;	mirrortime->setsize(120, 25);
		mirrortime->setpos(1045, 390);
		mirrortime->setcolor(192, 192, 216);
		mirrortime->setemptycolor(0, 0, 0, 0);		
		mirrortime->fill();
	}
	if (mirrortime&&!(bd->mirrorP))
	{
		delete mirrortime;
		mirrortime = nullptr;
	}

	std::ostringstream ss;
	ss << "lives: " << bd->lives << "\nscore: " << bd->score << "\nshield HP: " << bd->shieldHP
		<< "\ndmg mult:" << bd->dmgmult << "\n\nballs:"<<bd->getballc();

	pboost.fill(bd->pboost / 1.2);	//max pboost=120

	infot.setString(ss.str());
	w->draw(infop);
	w->draw(infot);
	w->draw(infop2);
	pboost.show(w);
	if (mirrortime)
	{
		mirrortime->fill(bd->mirrortime / bd->maxmirrortime * 100);
		mirrortime->show(w);
	}
}

interf::interf(board*bd)
{
	this->bd = bd;
	infop.setFillColor(sf::Color::Color(128, 240, 128));
	infop.setSize(sf::Vector2f(165, 300));
	infop.setPosition(1025, 10);
	infop.setOutlineThickness(5);
	infop.setOutlineColor(sf::Color::Color(64, 128, 64));

	infop2.setFillColor(sf::Color::Color(255, 192, 108));
	infop2.setSize(sf::Vector2f(165, 300));
	infop2.setPosition(1025, 325);	
	infop2.setOutlineThickness(5);
	infop2.setOutlineColor(sf::Color::Color(228, 96, 54));

	if (!f.loadFromFile("sansation.ttf"))
	{
		//err
	}
	infot.setFont(f);
	infot.setCharacterSize(20);
	infot.setPosition(1035, 20);
	infot.setFillColor(sf::Color::Color(0, 0, 255));

	infot2.setFont(f);
	infot2.setCharacterSize(20);
	infot2.setPosition(1035, 20);
	infot2.setFillColor(sf::Color::Color(0, 0, 255));


	pboost.setsize(120, 25);
	pboost.setpos(1045, 340);
	pboost.setcolor(64, 192, 255);
	pboost.setemptycolor(0, 0, 0, 0);
	pboost.fill(50);

}


interf::~interf()
{
}
