#include "text.h"

TextEntity::TextEntity(std::string text, std::string font_path, int size, sf::Color color, int posx, int posy)
{
	this->font.loadFromFile(font_path);
	this->txt = new sf::Text();
	this->txt->setFont(this->font);
	this->txt->setPosition(posx, posy);
	this->txt->setOutlineColor(sf::Color::Black);
	this->txt->setOutlineThickness(4.f);

	this->txt->setString(text);
	this->txt->setFillColor(color);
	this->txt->setCharacterSize(size);
}

void TextEntity::draw_on_screen(sf::RenderWindow* win)
{
	win->draw(*this->txt);
}

void TextEntity::setString(std::string str)
{
	this->txt->setString(str);
}


TextEntity::~TextEntity() {
	delete this->txt;
}