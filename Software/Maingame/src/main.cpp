#include <iostream>
#include "sqlite3.h"
#include "sql.hpp"
#include <SFML\Graphics.hpp>
#include "npc.hpp"
#include "button_actions.hpp"



// https://dcravey.wordpress.com/2011/03/21/using-sqlite-in-a-visual-c-application/
// https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
// http://www.w3schools.com/sql
// If you get a lot of '1's when executing a query, you might miss some parameters


int main( int argc, char* argv[]) {
	sql database;
	int current_save = 1;
	std::cout << "Checking CMD" << std::endl;
	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	
	npc player(window, "../../bin/sprite_sheets/player_sprite.png", { 100,100 }, true);

	//std::cout << database.get_player_variable(current_save, "name");
	//std::cout << database.get_data_from_query("SELECT sprites.path FROM sprites, player WHERE player.sprite_id == sprites.id");
	std::vector<npc*>npc_list;
	std::vector<std::string>npc_names;
	std::vector<std::string>lalalal;
	lalalal = database.get_npc_variables();
	
	for (auto indexer : lalalal) {
		std::cout << indexer << "\t";
	}
	


	while (window.isOpen()) {
		window.clear();
		
		
		player.set_action(get_action_name_from_button_keys());
		player.move_player(get_move_direction_from_button_keys());
		player.draw();
		


		window.display();


		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}


		sf::sleep(sf::milliseconds(10));
	}


	//database.get_data("NPC", "id");

	//database.change_data("item", "name", "'apple'", "name", "banana");
	//database.execute_query("SELECT name FROM item ORDER BY id DESC");
	//database.add_data("item", "'Tokato gloves', 0, 20, 0, 60");
	

	
	//database.get_data("item", "name");

	while (1) {}
}
