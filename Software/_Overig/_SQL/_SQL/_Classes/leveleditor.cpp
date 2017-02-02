#include "leveleditor.hpp"

leveleditor::leveleditor(sf::Vector2f levelsize, sf::Vector2f rect_size, sf::RenderWindow & window):
	levelsize(levelsize),
	rect_size(rect_size),
	window(window)
{
	load_rectangles();
	load_tile_list();

	view1.setCenter(sf::Vector2f(levelsize.x / 2, levelsize.y / 2));
	view1.setSize(sf::Vector2f(levelsize.x, levelsize.y));
	view1.setViewport(sf::FloatRect(0, 0, 0.75f, 1));

	view2.setCenter(sf::Vector2f(levelsize.x + rect_size.x*3, 50));
	view2.setSize(sf::Vector2f(rect_size.x*2, 100));
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
			background_store.push_back(new picture(tile->picture_path, { pos }));
		}
	}
}

void leveleditor::remove_last_object() {
	if (background_store.size() > 0) {
		background_store.pop_back();
	}
}

void leveleditor::load_tile_list() {
	float pos_x = levelsize.x + (rect_size.x*2);
	float pos_y = 0;
	bool count = false;
	for(auto path : path_array){
		tile_store.push_back(new picture(path ,{pos_x, pos_y})); 
		if (count == false) {
			pos_x += rect_size.x;
			count = true;
		}
		else if (count == true) {
			pos_y += rect_size.y;
			pos_x -= rect_size.x;
			count = false;
		}
	}
}

sf::Vector2f leveleditor::convert_to_coords() {
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

sf::Vector2f leveleditor::get_position_from_rectangle_under_mouse() {
	for (auto rectangle : rectangle_store) {
		if (rectangle->getBounds().contains(convert_to_coords())) {
			return rectangle->position;
		}
	}
	return {0,0};
}

void leveleditor::set_selected() {
	for (auto tile : tile_store) {
		if (tile->getBounds().contains(convert_to_coords())){
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