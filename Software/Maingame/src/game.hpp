#ifndef _game_HPP
#define _game_HPP

#include <SFML\Graphics.hpp>
#include <iostream>
#include "sqlite3.h"
#include "sql.hpp"
#include <functional>
#include "objects.hpp"

class game {
private:
	sf::RenderWindow & window;
	sf::View game_view;
	std::vector<picture*> background_store;
	sql & database;
	sf::Vector2f levelsize;
	std::map<std::string, std::vector<std::string>>background_values_map;
	std::map<std::string, std::vector<std::string>>object_values_map;
	void draw_background_store();
public:
	game(sf::RenderWindow & window, sql & database, sf::Vector2f levelsize);
	void game_loop();
	void get_items_from_database(std::map<std::string, std::vector<std::string>> & item_values_map);
};

#endif
