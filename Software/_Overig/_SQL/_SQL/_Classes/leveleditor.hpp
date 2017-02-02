#ifndef _leveleditor_HPP
#define _leveleditor_HPP

#include "objects.h"
#include <functional>

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
public:
	leveleditor(sf::Vector2f levelsize, sf::Vector2f tilesize, sf::RenderWindow & window);
	sf::View view1;
	sf::View view2;

	void editor_loop();
	void get_actions();
	void draw_rectangle_store();
	void draw_background_store();
	void draw_tile_store();

private:
	sf::Vector2f levelsize = { 0,0 };
	sf::Vector2f rect_size = { 0,0 };
	std::vector<figure*> rectangle_store;
	std::vector<figure*> background_store;
	std::vector<picture*> tile_store;
	sf::RenderWindow & window;

	void load_rectangles();
	void load_tile_list();
	void set_selected();
	void remove_last_object();
	void create_object(sf::Vector2f position);
	sf::Vector2f convert_to_coords();
	sf::Vector2f get_position_from_rectangle_under_mouse();

	const std::vector<std::string> path_array = { "grass.png","water.png","water_light.png","wood.png","wall.png","dakpan_links.png", "dakpan_rechts.png","gravel_left.png","gravel_right.png","iron.png","castle_wall.png" };
	action actions[11] = {
		action(sf::Keyboard::Left,  [&]() {view1.move(-16, 0); }),
		action(sf::Keyboard::Right, [&]() {view1.move(16, 0); }),
		action(sf::Keyboard::Up,    [&]() {view1.move(0, -32); }),
		action(sf::Keyboard::Down,  [&]() {view1.move(0, 32); }),
		action(sf::Keyboard::Z,     [&]() {view1.zoom(0.9f); }),
		action(sf::Keyboard::X,		[&]() {view1.zoom(1.1f); }),
		action(sf::Mouse::Left,     [&]() {create_object(get_position_from_rectangle_under_mouse()); }),
		action(sf::Mouse::Right,	[&]() {set_selected(); }),
		action(sf::Keyboard::S,		[&]() {view2.move(0,5); }),
		action(sf::Keyboard::W,		[&]() {view2.move(0,-5); }),
		action(sf::Keyboard::C,     [&]() {remove_last_object(); })
	};
};

#endif
