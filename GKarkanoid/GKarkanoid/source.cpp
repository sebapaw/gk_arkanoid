#include <SFML/Graphics.hpp>
#include <cmath>
#include "interf.h"
#include <ctime>
int main()
{
	srand(time(0));
	sf::RenderWindow wi(sf::VideoMode(1250, 800), "a");
	wi.setFramerateLimit(120);

	board bd;
	interf inf(&bd);
	
	sf::Clock stoper;
	while (wi.isOpen())
	{
		sf::Event event; while (wi.pollEvent(event)) { if (event.type == sf::Event::Closed)wi.close(); } //while
		wi.clear();

		bd.update(0.015);
		bd.draw(&wi);
		inf.draw(&wi);
		wi.display();
	} //while
	return 0;
}