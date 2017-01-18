#include "level.hpp"



level::level(std::string level_data_path):
	level_background(level_data_path)
{
	input.open(level_data_path);
	if (!input.is_open()) {
		throw unknown_tile(level_data_path);
	}
	input >> level_name;
}

void level::draw(sf::RenderWindow & window) {
	level_background.draw(window);
}

std::string level::get_name() {
	return level_name;
}


level::~level(){}
