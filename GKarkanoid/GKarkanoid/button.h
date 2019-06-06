#pragma once
#include <SFML/Graphics.hpp>
class button :public sf::RectangleShape
{
	sf::Text t;
	sf::Font f;
	bool clicked = 0;
public:

	void set(std::string s) { t.setString(s); }
	void set(int x, int y);
	void set(int x, int y, std::string s) { set(x, y); t.setString(s); }
	void setcolor(int r, int g, int b, int a = 255) { setFillColor(sf::Color::Color(r, g, b, a)); }
	void setsize(float x, float y) { setSize(sf::Vector2f(x, y)); }
	void show(sf::RenderWindow*);
	button();
	~button();
	bool checkclick(bool click, sf::Vector2i pos);
};

