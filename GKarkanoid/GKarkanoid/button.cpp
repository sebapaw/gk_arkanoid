#include "button.h"




void button::set(int x, int y)
{
	setPosition(x, y);
	t.setPosition(x + 5, y + 10);
}

void button::show(sf::RenderWindow *w)
{
	w->draw(*this);
	w->draw(t);

}

button::button()
{
	setFillColor(sf::Color::Color(200, 200, 200));
	setSize(sf::Vector2f(100, 50));
	if (!f.loadFromFile("sansation.ttf"))
	{
		//err
	}
	t.setFont(f);
	t.setFillColor(sf::Color::Color(0, 0, 0));
	t.setCharacterSize(20);


}


button::~button()
{
}

bool button::checkclick(bool click, sf::Vector2i pos)
{
	if (click)
	{
		if (!clicked&&pos.x >= getPosition().x&&pos.y >= getPosition().y&&pos.x <= (getPosition().x + getSize().x) && pos.y <= (getPosition().y + getSize().y))
		{
			clicked = 1;
			return true;
		}
		clicked = 1;
	}
	else
		clicked = 0;




	return false;
}
