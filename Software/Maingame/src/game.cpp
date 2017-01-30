#include "game.hpp"

game::game(sf::RenderWindow & window, sql & database, sf::Vector2f levelsize) :
	window(window),
	database(database),
	levelsize(levelsize),
	arno(window, database, "1"),
	dialogbox("../../bin/pictures/dialog_box.png", "../../bin/pictures/game_font.ttf", {200, 800})
	
{
	background_values_map = database.get_level_background_value("17");
	get_items_from_database(background_values_map);
	object_values_map = database.get_level_object_value("17");
	get_items_from_database(object_values_map);
	load_npc();
	draw_npc();
	draw_player();
	game_view.setCenter(levelsize.x / 2 + 25, levelsize.y / 2 + 10);
	game_view.setSize(levelsize.x, levelsize.y);
	game_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	game_view.zoom(1.2);
}

void game::game_loop() {
	while (window.isOpen()) {
		
		window.clear();
		


		window.setView(game_view);
		draw_background_store();
		if (game_begin == false) {
			view_start_dialogs();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::R));
			//arno.respawn();
		}
		draw_npc();
		move_player();
		draw_player();
		
		
		window.display();
		
		

		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			sf::sleep(sf::milliseconds(10));
		}
	}
}

void game::view_start_dialogs() {
	while (game_begin == false) {
		if (count == 0) {
			dialogbox.text_input(game_intro, 25, sf::Color::White);
			dialogbox.draw(window);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				sf::sleep(sf::milliseconds(200));
				count = 1;
			}
		}
		if (count == 1) {
			dialogbox.text_input(tutorial_sentence, 25, sf::Color::White);
			dialogbox.draw(window);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				sf::sleep(sf::milliseconds(200));
				game_begin = true;
			}
		}
		window.display();
	}
}

void game::get_items_from_database(std::map<std::string, std::vector<std::string>> & item_values_map) {
	std::string path;
	float posx = 0;
	float posy = 0;
	for (auto map_indexer = item_values_map.begin(); map_indexer != item_values_map.end(); map_indexer++) {
		path = map_indexer->second.at(0);
		posx = std::stof(map_indexer->second.at(2));
		posy = std::stof(map_indexer->second.at(3));
		sf::Vector2f pos = { posx, posy };
		std::cout << "loaded: " << path << "\t" << pos.x << "\t" << pos.y << "\n";
		background_store.push_back(new picture(path, pos, { 0,0 }));
	}
}

void game::draw_background_store() {
	for (auto background_tile : background_store) {
		background_tile->draw(window);
	}
}


void game::draw_npc() {
	for (auto one_npc : npc_list) {
		one_npc->draw();
	}
}

void game::load_npc() {
	for (auto indexer : database.get_number_of_npcs()) {
		npc_list.push_back(new npc(window, database, indexer));
	}
}


void game::move_player() {
	for (auto one_npc : npc_list) {
		if (!arno.get_interaction(*one_npc)) {
			arno.set_action(get_action_name_from_button_keys());
			arno.move(get_move_direction_from_button_keys());
		}

		else if (arno.get_interaction(*one_npc)) {
			for (int i = 0; i < 5; i++) {
				//arno.set_last_position();
			}
			std::cout << "Collision" << std::endl;
		}
	}
	
}

void game::draw_player() {
	//std::cout << "(" << arno.get_position().x << " , " << arno.get_position().x << ")\n";
	arno.draw();
}




