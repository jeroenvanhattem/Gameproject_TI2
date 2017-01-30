#ifndef _dialogbox_HPP
#define _dialogbox_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "objects.hpp"

class dialogbox{
private:
	sf::Text text;
	sf::Font font;
	std::string font_path;
	sf::Vector2f position;
	
	picture box;
public:
	dialogbox(std::string box_path, std::string font_path, sf::Vector2f position);
	void draw(sf::RenderWindow & window);
	void text_input(std::string sentence, int char_size, sf::Color color);
};

#endif
