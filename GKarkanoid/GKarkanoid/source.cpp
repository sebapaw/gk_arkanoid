#include <SFML/Graphics.hpp>
#include <cmath>
#include "board.h"
#include "interf.h"
#include <ctime>
int main()
{
	srand(time(0));
	sf::RenderWindow wi(sf::VideoMode(1200, 800), "a");
	wi.setFramerateLimit(60);

	board bd;
	interf inf(&bd);
	bd.adddefblocks();

	sf::Clock stoper;
	while (wi.isOpen())
	{
		sf::Event event; while (wi.pollEvent(event)) { if (event.type == sf::Event::Closed)wi.close(); } //while
		wi.clear();

		bd.update(0.03);
		bd.draw(&wi);
		inf.draw(&wi);
		wi.display();
	} //while
	return 0;
}