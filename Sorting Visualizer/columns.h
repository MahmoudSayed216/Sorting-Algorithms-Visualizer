#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>


class column
{

public:

	uint32_t  width;
	sf::RectangleShape* unit;
	column();

	column(int, int, int, int, sf::Color = sf::Color::White);

	static void swap(column& c1, column& c2);
	void draw_on_screen(sf::RenderWindow*);
	int get_height();
	void set_height(int w, int h);

	//~column();
	
};

