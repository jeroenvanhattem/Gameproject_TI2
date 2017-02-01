#include "game.hpp"

game::game(sf::RenderWindow & window, sql & database, sf::Vector2f levelsize) :
	window(window),
	database(database),
	levelsize(levelsize),
	arno(window, database, "1"),
	dialogbox("../../bin/pictures/dialog_box.png", "../../bin/pictures/game_font.ttf", {200, 800})
	
{
	std::vector<std::string>level_ids = database.get_level_ids();
	if (!level_ids.empty()) {
		background_values_map = database.get_level_background_value(level_ids.at(0));

		for (auto indexer = background_values_map.begin(); indexer != background_values_map.end(); indexer++) {
			if (indexer->second.at(indexer->second.size() - 1) != "1") {
				std::cout << indexer->second.at(1);
				collision_objects.push_back(database.get_collision_objects(indexer->second));
			}
		}

		get_items_from_database(background_values_map);
		object_values_map = database.get_level_object_value(level_ids.at(0));

		for (auto indexer = object_values_map.begin(); indexer != object_values_map.end(); indexer++) {
			collision_backgrounds.push_back(database.get_collision_objects(indexer->second));
		}
		get_items_from_database(object_values_map);
		load_npc();
		draw_npc();
		draw_player();
	}
	game_view.setCenter(levelsize.x / 2 + 25, levelsize.y / 2 + 10);
	game_view.setSize(levelsize.x, levelsize.y);
	game_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	game_view.zoom(1.2f);
}

void game::game_loop() {
	
	while (window.isOpen()) {
		window.clear();
		
		if (game_begin) {
			window.setView(game_view);
			
			draw_background_store();
			move_player();
			draw_player();
			draw_npc();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::R));
				arno.respawn();
				std::cout << "(" << window.mapPixelToCoords(sf::Mouse::getPosition(window),game_view).x << " , " << window.mapPixelToCoords(sf::Mouse::getPosition(window), game_view).y << ")\n";
			}
		}
		else {
			view_start_dialogs();
		}
		
		interact("1");

		window.display();
		
		
		

		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			sf::sleep(sf::milliseconds(1));
		}
	}
}

void game::view_start_dialogs() {
	for (auto indexer : database.get_quest_parts("1")) {
		for (auto index : database.get_quest_text("1",indexer)) {
			if (index == "NULL") { continue; }
			dialogbox.text_input((index), 25, sf::Color::White);
			window.setView(game_view);
			dialogbox.draw(window);
			window.display();

			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
		}
	}

	game_begin = true;
	window.clear();
	draw_player();
	perform_player_action("cast_spell_down");
	window.display();
	sf::sleep(sf::milliseconds(1000));
}

void game::interact() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		for (auto one_npc : npc_list) {
			if (arno.get_interaction(*one_npc)) {

				for (auto indexer : database.get_quest_parts("0")) {
					for (auto index : database.get_quest_text("0", indexer)) {
						if (index == "NULL") { continue; }
						dialogbox.text_input((index), 25, sf::Color::White);
						window.setView(game_view);
						dialogbox.draw(window);
						window.display();

						while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
						while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
					}
				}
			}
		}

		window.clear();
		draw_player();
		window.display();
	}
}

void game::interact(std::string item_id) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		for (auto one_npc : npc_list) {
			if (arno.get_interaction(*one_npc)) {
				for (auto indexer : database.get_quest_parts("2")) {
					for (auto index : database.get_quest_text("2", indexer)) {
						if (index == "NULL") { continue; }
						dialogbox.text_input((index), 25, sf::Color::White);
						window.setView(game_view);
						dialogbox.draw(window);
						window.display();

						while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
						while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
					}
				}
				database.add_item_to_inventory(item_id);
				//database.add_data("inventory", "1, 1, 0");
			}
		}

		window.clear();
		draw_player();
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
	bool no_collision = true;
	for (auto one_npc : npc_list) {
		if (arno.get_interaction(*one_npc)) {
			no_collision = false;
		}
	}
	for (auto indexer : collision_backgrounds) {
		if (arno.get_collision(indexer)) {
			no_collision = false;
		}
	}
	for (auto indexer : collision_objects) {
		if (arno.get_collision(indexer)) {
			no_collision = false;
		}
	}
	if (no_collision) {
		arno.set_action(get_action_name_from_button_keys());
		arno.move(get_move_direction_from_button_keys());
	}
	else {
		for (int i = 0; i < 3; i++) {
			arno.set_last_position();
		}
	}
	
}

void game::draw_player() {
	arno.draw();
}

void game::perform_player_action(std::string action) {
	arno.show_action(action);
}

void game::perform_npc_action(std::string npc_name, std::string action) {
	for (auto indexer : npc_list) {
		if (indexer->get_name() == npc_name) {
			indexer->show_action(action);
		}
	}
}