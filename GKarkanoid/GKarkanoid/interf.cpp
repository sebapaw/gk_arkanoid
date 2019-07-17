#include "interf.h"
#include <sstream>


void interf::createmenu()
{
	menu = new sf::RectangleShape;
	menu->setFillColor(sf::Color::Color(100, 140, 180));
	menu->setPosition(400, 200);
	menu->setSize(sf::Vector2f(400, 300));
	
	startb = new button;
	startb->set(420, 420, "start");
	startb->setsize(150, 50);

	highb = new button;
	highb->set(420, 320, "high scores");
	highb->setsize(150, 50);

	option0 = new button;
	option0->set(620, 220, "");
	option0->setsize(30, 30);
	if (bd->option0)
		option0->setcolor(0, 150, 0);
	else
		option0->setcolor(200, 0, 0);

	
	optiontx.setCharacterSize(13);
	optiontx.setFont(f);
	optiontx.setPosition(660, 220);
	optiontx.setString("display block hp\ndivided by dmg mult");

}

void interf::showmenu(sf::RenderWindow*w)
{
	sf::Vector2i pos = sf::Mouse::getPosition(*w);
	bool mp = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	//if (highb->checkclick(mp, pos))

	if (option0->checkclick(mp, pos))
	{
		bd->option0 = !bd->option0;
		if (bd->option0)
			option0->setcolor(0, 150, 0);
		else
			option0->setcolor(200, 0, 0);
	}
	if (startb->checkclick(mp, pos))
	{
		bd->gamestate = 1;
		deletemenu();
		menu = nullptr;
	}

	if (menu)
	{
		w->draw(*menu);
		startb->show(w);
		highb->show(w);
		option0->show(w);
		w->draw(optiontx);
	}
}

void interf::draw(sf::RenderWindow*w)
{
	if (bd->gamestate == 0)
		if (!menu)
		{
			createmenu();
			showmenu(w);
		}
		else
			showmenu(w);
	if (bd->gamestate != 0 && menu)
	{
		deletemenu();
		menu = nullptr;
	}

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

	

	if (!stoptime&&bd->blockstop)
	{
		stoptime = new progbar;	stoptime->setsize(120, 25);
		stoptime->setpos(1045, 430);
		stoptime->setcolor(237, 28, 36);
		stoptime->setemptycolor(0, 0, 0, 0);
		stoptime->fill();
	}
	if (stoptime && !(bd->blockstop))
	{
		delete stoptime;
		stoptime = nullptr;
	}

	if (!magnettime&&bd->magnetON)
	{
		magnettime = new progbar;	magnettime->setsize(120, 25);
		magnettime->setpos(1045, 470);
		magnettime->setcolor(220,60,120);
		magnettime->setemptycolor(0, 0, 0, 0);
		magnettime->fill();
	}
	if (magnettime && !(bd->magnetON))
	{
		delete magnettime;
		magnettime = nullptr;
	}

	std::ostringstream ss,ss2;
	ss << "lives: " << bd->lives << "\nscore: " << bd->score << "\nshield HP: " << bd->shieldHP
		<< "\ndmg mult:" << bd->dmgmult << "\n\nballs:"<<bd->getballc();

	pboost.fill(bd->pboost / bd->maxfuel * 100);	
	ss2 << floor(bd->pboost) << "/" << bd->maxfuel;
	pboosttx.setString(ss2.str());

	infot.setString(ss.str());
	w->draw(infop);
	w->draw(infot);
	w->draw(infop2);
	pboost.show(w);
	w->draw(pboosttx);
	if (mirrortime)
	{
		mirrortime->fill(bd->mirrortime / bd->maxmirrortime * 100);
		mirrortime->show(w);
	}

	if (stoptime)
	{
		stoptime->fill(bd->stoptime / bd->maxstoptime * 100);
		stoptime->show(w);
	}

	if (magnettime)
	{
		magnettime->fill(bd->magnettime / bd->maxmagnettime * 100);
		magnettime->show(w);
	}
}

interf::interf(board*bd)
{
	this->bd = bd;
	infop.setFillColor(sf::Color::Color(128, 240, 128));
	infop.setSize(sf::Vector2f(245, 300));
	infop.setPosition(1025, 10);
	infop.setOutlineThickness(5);
	infop.setOutlineColor(sf::Color::Color(64, 128, 64));

	infop2.setFillColor(sf::Color::Color(255, 192, 108));
	infop2.setSize(sf::Vector2f(245, 300));
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

	pboosttx.setCharacterSize(20);
	pboosttx.setFont(f);
	pboosttx.setPosition(1170, 340);
	pboosttx.setFillColor(sf::Color::Color(0, 128, 255));
}


interf::~interf()
{
}
