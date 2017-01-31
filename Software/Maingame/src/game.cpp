#include "game.hpp"

game::game(sf::RenderWindow & window, sql & database, sf::Vector2f levelsize) :
	window(window),
	database(database),
	levelsize(levelsize),
	dialogbox("../../bin/pictures/dialog_box.png", "../../bin/pictures/game_font.ttf", {200, 800})
{
	std::vector<std::string>level_ids = database.get_level_ids();
	background_values_map = database.get_level_background_value(level_ids.at(0));
	get_items_from_database(background_values_map);
	object_values_map = database.get_level_object_value(level_ids.at(0));
	get_items_from_database(object_values_map);

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
	for (auto map_indexer : item_values_map) {
		path = map_indexer.second.at(0);
		posx = std::stof(map_indexer.second.at(2));
		posy = std::stof(map_indexer.second.at(3));
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