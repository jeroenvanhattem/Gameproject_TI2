#ifndef _leveleditor_HPP
#define _leveleditor_HPP

#include "objects.hpp"
#include <functional>
#include <sstream>
#include <fstream>
#include "sql.hpp"

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action(std::function< bool() > condition, std::function< void() > work) :
		condition(condition),
		work(work)
	{}

	action(std::function< void() > work) :
		condition([]()->bool {return true; }),
		work(work)
	{}

	action(sf::Keyboard::Key key, std::function< void() > work) :
		condition([key]()->bool { return sf::Keyboard::isKeyPressed(key); }),
		work(work)
	{}

	action(sf::Mouse::Button button, std::function< void() > work) :
		condition([button]()->bool { return sf::Mouse::isButtonPressed(button); }),
		work(work)
	{}

	void operator()() {
		if (condition()) {
			work();
		}
	}
};

class leveleditor {
private:
	sf::Vector2f levelsize = { 0,0 };
	sf::Vector2f rect_size = { 0,0 };
	std::vector<figure*> rectangle_store;
	std::vector<figure*> background_store;
	std::vector<picture*> tile_store;
	sf::RenderWindow & window;
	sql & database;
	picture back_to_menu_button;
	picture save_level_button;
	picture new_game_button;
	picture load_game_button;
	picture level_1_button;
	picture level_2_button;
	picture level_3_button;

	void load_rectangles();
	void load_tile_list();
	void set_selected();
	void remove_last_object();
	bool remove_object_under_mouse();
	void create_object(sf::Vector2f position);
	sf::Vector2f convert_to_coords(sf::View & view);
	sf::Vector2f get_position_from_rectangle_under_mouse();
	bool is_object_under_mouse(std::vector<picture*> & vector, sf::View & view);
	bool is_object_under_mouse(std::vector<figure*> & vector, sf::View & view);
	bool is_button_pressed(picture & object, sf::View & view);
	bool pressed_esc = true;
	bool pressed_load_game = false;

	action actions[12] = {
		action(sf::Keyboard::Left,  [&]() {view1.move(-16, 0); }),
		action(sf::Keyboard::Right, [&]() {view1.move(16, 0); }),
		action(sf::Keyboard::Up,    [&]() {view1.move(0, -32); }),
		action(sf::Keyboard::Down,  [&]() {view1.move(0, 32); }),
		action(sf::Keyboard::Z,     [&]() {view1.zoom(0.9f); }),
		action(sf::Keyboard::X,		[&]() {view1.zoom(1.1f); }),
		action(sf::Mouse::Left,     [&]() {if (is_object_under_mouse(rectangle_store, view1)) { create_object(get_position_from_rectangle_under_mouse()); } }),
		action(sf::Mouse::Left,		[&]() {if (is_object_under_mouse(tile_store, view2)) { set_selected(); } }),
		action(sf::Keyboard::S,		[&]() {view2.move(0,5); }),
		action(sf::Keyboard::W,		[&]() {view2.move(0,-5); }),
		action(sf::Keyboard::C,     [&]() {remove_object_under_mouse(); }),
		action(sf::Keyboard::BackSpace, [&]() {remove_last_object(); })
	};

public:
	leveleditor(sf::Vector2f levelsize, sf::Vector2f tilesize, sf::RenderWindow & window, sql & database);
	sf::View view1;
	sf::View view2;
	sf::View view3;
	sf::View view4;

	void editor_loop();
	void get_actions();
	void draw_rectangle_store();
	void draw_background_store();
	void draw_tile_store();
};

#endif
