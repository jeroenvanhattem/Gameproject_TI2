#include "game.hpp"

game::game(sf::RenderWindow & window, sql & database, sf::Vector2f levelsize):
	window(window),
	database(database),
	levelsize(levelsize)
{

	background_values_map = database.get_level_background_value("17");
	get_items_from_database(background_values_map);
	object_values_map = database.get_level_object_value("17");
	get_items_from_database(object_values_map);

	game_view.setCenter(levelsize.x/2, levelsize.y/2);
	game_view.setSize(levelsize.x, levelsize.y);
	game_view.setViewport(sf::FloatRect(0,0,1,1));
}

void game::game_loop() {
	while (window.isOpen()) {

		window.clear();
		window.setView(game_view);
		draw_background_store();
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

void game::get_items_from_database(std::map<std::string, std::vector<std::string>> & item_values_map) {
	std::string path;
	float posx = 0;
	float posy = 0;
	int count = 0;
	for (auto map_indexer = item_values_map.begin(); map_indexer != item_values_map.end(); map_indexer++) {
		count = 0;
		for (auto map_value_indexer : map_indexer->second) {
			if (count == 0) {
				path = map_value_indexer;
			}
			if (count == 2) {
				posx = std::stof(map_value_indexer);
			}
			if (count == 3) {
				posy = std::stof(map_value_indexer);
				sf::Vector2f pos = { posx, posy };
				std::cout << "loaded: " << path << "\t" << pos.x << "\t" << pos.y << "\n";
				background_store.push_back(new picture(path, pos, { 0,0 }));
			}
			count++;
		}
	}
}

void game::draw_background_store() {
	for (auto background_tile : background_store) {
		background_tile->draw(window);
	}
}