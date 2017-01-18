#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "background.hpp"

class level {
private:
	background level_background;
	std::string level_name;
	std::ifstream input;
public:
	level(std::string background_file_path);
	void draw(sf::RenderWindow & window);
	std::string get_name();
	~level();
};