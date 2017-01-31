#ifndef _game_HPP
#define _game_HPP

#include <SFML\Graphics.hpp>
#include <iostream>
#include "sqlite3.h"
#include "sql.hpp"
#include <functional>
#include "objects.hpp"
#include "dialogbox.hpp"

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
	bool game_begin = false;
	bool first_dialog_done = false;
	void view_start_dialogs();
	int count = 0;

	std::string tutorial_sentence = "Welcome, try to walk using the up, down, left or right keys.\n\nPress space to begin!";
	std::string game_intro = "Ouch, where am i?\n\nIt feels like i slept for hours and i can't remember a thing.\n\n[press space to continue])";
	dialogbox dialogbox;
public:
	game(sf::RenderWindow & window, sql & database, sf::Vector2f levelsize);
	void game_loop();
	void get_items_from_database(std::map<std::string, std::vector<std::string>> & item_values_map);
};

#endif
