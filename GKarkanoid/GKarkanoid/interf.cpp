#include "interf.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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

void interf::createhighscorescreen()
{
	highscore = new sf::RectangleShape;
	highscore->setFillColor(sf::Color::Color(100, 140, 180));
	highscore->setPosition(300, 100);
	highscore->setSize(sf::Vector2f(600, 600));

	backb = new button;
	backb->set(420, 220, "back");
	backb->setsize(150, 50);

	if (!fileread)
	{
		ifstream highscoref;
		highscoref.open("highscore.txt");
		if (!highscoref.fail())
		{
			string str;
			while (std::getline(highscoref, str))
			{
				hsname.push_back(str.substr(0, 3));
				size_t pos = str.find(" ");
				hsvalue.push_back(stoi(str.substr(pos + 1)));
				it++;
			}
			//if (bd->score > hsvalue.at(hsvalue.size()) || (hsvalue.size()<10 && bd->score != 0))
			fileread = true;
			highscoref.close();
		}
		string highscorestr = "";

		for (int i = 0;i < hsname.size();i++)
		{
			highscorestr += to_string(i + 1);
			if(i==0)
				highscorestr += "   | ";
			if(i>0 && i<9)
				highscorestr += "  | ";
			if(i==9)
				highscorestr += " | ";
			highscorestr += hsname.at(i);
			highscorestr += " | ";
			highscorestr += to_string(hsvalue.at(i));
			highscorestr += "\n";

		}
		highscorelist.setString(highscorestr);
		highscorelist.setFont(f);
		highscorelist.setPosition(620, 210);
		highscorelist.setCharacterSize(40);
		highscorelist.setFillColor(sf::Color(220, 220, 220));
	}
}

void interf::creategameoverscreen()
{
	gameover = new sf::RectangleShape;
	gameover->setFillColor(sf::Color::Color(100, 140, 180));
	gameover->setPosition(400, 200);
	gameover->setSize(sf::Vector2f(400, 300));

	gameoverb = new button;
	gameoverb->set(420, 420, "exit");
	gameoverb->setsize(150, 50);

	gameovert.setFont(f);
	gameovert.setPosition(520, 210);
	gameovert.setCharacterSize(40);
	gameovert.setString("Game Over");
	gameovert.setFillColor(sf::Color(200, 30, 30));

	
}

void interf::createnewRecord()
{
	newRecord = new sf::RectangleShape;
	newRecord->setFillColor(sf::Color::Color(100, 140, 180));
	newRecord->setPosition(400, 200);
	newRecord->setSize(sf::Vector2f(400, 300));

	newscoret.setFont(f);
	newscoret.setPosition(520, 210);
	newscoret.setCharacterSize(20);
	newscoret.setString("New highscore!\nEnter your name");
	newscoret.setFillColor(sf::Color(200, 30, 30));

	newscorenamet.setFont(f);
	newscorenamet.setPosition(500, 280);
	newscorenamet.setCharacterSize(100);
	newscorenamet.setString("");
	newscorenamet.setFillColor(sf::Color(30, 30, 30));
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

	if (highb->checkclick(mp, pos))
	{
		createhighscorescreen();
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

void interf::showhighscorescreen(sf::RenderWindow * w)
{
	sf::Vector2i pos = sf::Mouse::getPosition(*w);
	bool mp = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	//if (highb->checkclick(mp, pos))

	if (backb->checkclick(mp, pos))
	{
		deletehighscorescreen();
		highscore = nullptr;
		createmenu();
	}

	if (highscore)
	{
		w->draw(*highscore);
		backb->show(w);
		w->draw(highscorelist);
	}
}

void interf::showgameoverscreen(sf::RenderWindow * w)
{
	sf::Vector2i pos = sf::Mouse::getPosition(*w);
	bool mp = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	//if (highb->checkclick(mp, pos))

	if (gameoverb->checkclick(mp, pos))
	{
		w->close();
	}

	if (gameover)
	{
		w->draw(*gameover);
		gameoverb->show(w);
		w->draw(gameovert);
	}
}

void interf::shownewRecord(sf::RenderWindow * w)
{
	sf::Vector2i pos = sf::Mouse::getPosition(*w);
	bool mp = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	//if (highb->checkclick(mp, pos))
	if (scoreinput.size()==3)
	{
		bd->scoresaved = true;
		newRecord = nullptr;
	}
	sf::Event event;
	while (w->pollEvent(event) && scoreinput.size()<3) 
	{ 
		if (event.type == sf::Event::TextEntered)
		{
			if (scoreinput.size() < 3)
			{
				scoreinput += event.text.unicode;
				newscorenamet.setString(scoreinput);
			}
			
		}
		if (scoreinput.size() == 3)
			break;
	}

	if (newRecord)
	{
		w->draw(*newRecord);
		w->draw(newscoret);
		w->draw(newscorenamet);
		w->draw(nameunderfield);
	}
	else
	{
		ofstream highscoref;
		highscoref.open("highscore.txt");
		int iter = 0;
		bool saved = false;
		if (highscoref.is_open())
		{
			int i;
			for (i = 0;i < hsname.size();i++)
			{
				if (i < 10)
				{
					if (bd->score > hsvalue.at(i) && !saved)
					{
						highscoref << scoreinput << " " << to_string(bd->score) << "\n";
						saved = true;
					}
					else
					{
						highscoref << hsname.at(iter) << " " << to_string(hsvalue.at(iter)) << "\n";
						iter++;
					}
					
				}
			}
			if (!saved && i<10)
			{
				highscoref << scoreinput << " " << to_string(bd->score) << "\n";
			}
			highscoref.close();
		}
		updscore = true;
		if (!gameover)
		{
				creategameoverscreen();
				showgameoverscreen(w);

		}
		else
		{
				showgameoverscreen(w);
		}
	}
}

void interf::draw(sf::RenderWindow*w)
{
	if (bd->gamestate == 0)
		if (!menu)
		{
			if (!highscore)
			{
				createmenu();
				showmenu(w);
			}
			else
				showhighscorescreen(w);
			
		}
		else
		{
			showmenu(w);
		}
			
	if (bd->gamestate != 0 && menu)
	{
		deletemenu();
		menu = nullptr;
	}

	if (bd->gamestate == 99)
	{
		//bd->score = 999;
		
		//int it=0;
		if (!fileread)
		{
			ifstream highscoref;
			highscoref.open("highscore.txt");
			if (!highscoref.fail())
			{
				string str;
				while (std::getline(highscoref, str))
				{
					hsname.push_back(str.substr(0, 3));
					size_t pos = str.find(" ");
					hsvalue.push_back(stoi(str.substr(pos + 1)));
					it++;
				}
				//if (bd->score > hsvalue.at(hsvalue.size()) || (hsvalue.size()<10 && bd->score != 0))
				fileread = true;
				highscoref.close();
			}
		}

		if (!bd->scoresaved)
		{
			if (it < 10 || bd->score > hsvalue.at(it - 1))
			{
				if (bd->score != 0)
				{
					updscore = false;
					if (!newRecord)
					{
						createnewRecord();
						shownewRecord(w);
					}
					else
						shownewRecord(w);
				}

			}
		}
		
			if (!gameover)
			{
				if (updscore)
				{
					creategameoverscreen();
					showgameoverscreen(w);
				}
				
			}
			else
			{
				if(updscore)
					showgameoverscreen(w);
			}
				
		

		//bd->scoresaved = true;
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
