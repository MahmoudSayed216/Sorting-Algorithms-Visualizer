#include "columns.h"

column::column()
{
	width = 0;
	unit = 0;
}

column::column(int w, int h, int x, int y, sf::Color clr) {
	width = w;
	unit = new sf::RectangleShape(sf::Vector2f(w, h));
	unit->setFillColor(clr);
	unit->setOrigin(0, h);
	unit->setPosition(x, y);
}

void column::swap(column& c1, column& c2)
{
	column temp = c1;
	int tempx = c1.unit->getPosition().x;
	int tempy = c1.unit->getPosition().y;
	c1 = c2;
	c2 = temp;
	c2.unit->setPosition(c1.unit->getPosition().x, c1.unit->getPosition().y);
	c1.unit->setPosition(tempx, tempy);
}

void column::draw_on_screen(sf::RenderWindow* win)
{
	win->draw(*this->unit);
}

int column::get_height()
{
	return this->unit->getGlobalBounds().height;
}

void column::set_height(int w, int h)
{
	this->unit->setSize(sf::Vector2f(w, h));
}



//column::~column()
//{
//	delete this->unit;
//}
//

