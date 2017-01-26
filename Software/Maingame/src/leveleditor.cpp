#include "leveleditor.hpp"

leveleditor::leveleditor(sf::Vector2f levelsize, sf::Vector2f rect_size, sf::RenderWindow & window, sql & database):
	levelsize(levelsize),
	rect_size(rect_size),
	database(database),
	window(window)
{
	load_rectangles();
	load_tile_list();

	view1.setCenter(sf::Vector2f(levelsize.x / 2, levelsize.y / 2));
	view1.setSize(sf::Vector2f(levelsize.x, levelsize.y));
	view1.setViewport(sf::FloatRect(0, 0, 0.75f, 1));
	view1.zoom(1.5);

	view2.setCenter(sf::Vector2f(levelsize.x + 192, 256));
	view2.setSize(sf::Vector2f(256, 512));
	view2.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 1));
}

void leveleditor::editor_loop() {
	window.setView(view1);
	get_actions();
	draw_rectangle_store();
	draw_background_store();
	window.setView(view2);
	get_actions();
	draw_tile_store();
}

void leveleditor::load_rectangles(){
	for (float x = 0; x <= levelsize.x; x += rect_size.x) {
		for (float y = 0; y <= levelsize.y; y += rect_size.y) {
			sf::Vector2f position = {x, y};
			rectangle_store.push_back(new rectangle(position, rect_size, 3, sf::Color::Black, sf::Color::Red));
		}
	}
}

void leveleditor::create_object(sf::Vector2f pos) {
	for (auto tile : tile_store) {
		if (tile->selected) {
			background_store.push_back(new picture(tile->picture_path, pos , tile->tile_size));
		}
	}
}

void leveleditor::remove_last_object() {
	if (background_store.size() > 0) {
		background_store.pop_back();
	}
}

bool leveleditor::remove_object_under_mouse() {
	int index = 0;
	for (auto tile : background_store) {
		if (tile->getBounds().contains(convert_to_coords(view1))) {
			background_store.erase(background_store.begin() + index);
			return true;
		}
		index += 1;
	}
	return false;
}

/*
std::ifstream & operator >> (std::ifstream & input, sf::Vector2f & rhs) {
	char c;
	if (!(input >> c)) {}
	//	if (c != '(') { throw invalid_position(c); }

	if (!(input >> rhs.x)) {}

	if (!(input >> c)) {}

	if (!(input >> rhs.y)) {}

	if (!(input >> c)) {}
	//	if (c != ')') { throw invalid_position(c); }
	return input;
}
*/

void leveleditor::save() {

}

void leveleditor::load_tile_list() {
	float start = levelsize.x + 64;
	float pos_x = levelsize.x + 64;
	float pos_y = 0;
	sf::Vector2f pre_size = { 0, 0 };
	std::string path;
	sf::Vector2f tile_size;
	float biggest_tile = 0;
	
	std::vector<std::string> tile_id;
	tile_id = database.get_object_sprite_ids();

	std::vector<std::string> tile;

	int tile_position_x_converted_as_int;
	int tile_position_y_converted_as_int;

	
	
	for (auto indexer : tile_id) {
		
		tile = database.get_object_sprite_value(indexer);

		std::istringstream buffer(tile.at(3));
		buffer >> tile_position_x_converted_as_int;
		std::istringstream buffer(tile.at(4));
		buffer >> tile_position_y_converted_as_int;
		

		sf::Vector2f tile_size = { tile_position_x_converted_as_int, tile_position_y_converted_as_int };
		
		if ((pos_x + tile_size.x) > (start + 256)) {
			pos_y += biggest_tile;
			pos_x = start;
			pre_size = { tile_size.x, tile_size.y };
			biggest_tile = 0;
		}
		if ((pos_x + tile_size.x) <= (start + 256)) {
			tile_store.push_back(new picture(tile.at(1), { pos_x, pos_y }, tile_size));
			pos_x += tile_size.x;
			pre_size = { tile_size.x, tile_size.y };
			if (pre_size.y > biggest_tile) {
				biggest_tile = pre_size.y;
			}
		}
	}
}

sf::Vector2f leveleditor::convert_to_coords(sf::View & view) {
	return window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
}

sf::Vector2f leveleditor::get_position_from_rectangle_under_mouse() {
	for (auto rectangle : rectangle_store) {
		if (rectangle->getBounds().contains(convert_to_coords(view1))) {
			return rectangle->position;
		}
	}
	return {0,0};
}

bool leveleditor::is_object_under_mouse(std::vector<figure*> & vector, sf::View & view) {
	for (auto tile : vector) {
		if (tile->getBounds().contains(convert_to_coords(view))) {
			return true;
		}
	}
	return false;
}

bool leveleditor::is_object_under_mouse(std::vector<picture*> & vector, sf::View & view) {
	for (auto tile : vector) {
		if (tile->getBounds().contains(convert_to_coords(view))) {
			return true;
		}
	}
	return false;
}

void leveleditor::set_selected() {
	for (auto tile : tile_store) {
		if (tile->getBounds().contains(convert_to_coords(view2))){
			tile->selected = 1;
		}
		else {
			tile->selected = 0;
		}
	}
}

void leveleditor::draw_rectangle_store() {
	for (auto rectangle : rectangle_store) {
		rectangle->draw(window);
	}
}

void leveleditor::draw_background_store() {
	for (auto background_tile : background_store) {
		background_tile->draw(window);
	}
}

void leveleditor::draw_tile_store() {
	for (auto tile : tile_store) {
		tile->draw(window);
	}
}

void leveleditor::get_actions() {
	for (auto & action : actions) {
		action();
	}
}