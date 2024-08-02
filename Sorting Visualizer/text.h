#pragma once
#include<string>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>



class TextEntity
{
public:
	TextEntity(std::string text, std::string font_path, int size, sf::Color color, int posx, int posy);
	void draw_on_screen(sf::RenderWindow*);
	void setString(std::string str);
	~TextEntity();
private:
	sf::Font font;
	int size;
	std::string text;
	sf::Color color;
	sf::Text *txt;
};
