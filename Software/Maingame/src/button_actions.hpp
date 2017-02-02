#pragma once
#include <SFML\Graphics.hpp>

const struct {
	
	sf::Keyboard::Key Key;
	std::string name;
	float x; float y;
}actions[] = {
	{ sf::Keyboard::Left,	"walk_left",	-2,  0 },
	{ sf::Keyboard::Right,	"walk_right",	+2,  0 },
	{ sf::Keyboard::Up,		"walk_up",		 0, -2 },
<<<<<<< HEAD
	{ sf::Keyboard::Down,	"walk_down",	 0, +2 },

	{ sf::Keyboard::A,	"walk_left",	-2,  0 },
	{ sf::Keyboard::D,	"walk_right",	+2,  0 },
	{ sf::Keyboard::W,	"walk_up",		 0, -2 },
	{ sf::Keyboard::S,	"walk_down",	 0, +2 }
};

const struct {

	sf::Keyboard::Key Key;
	sf::Mouse::Button mouse_key;
	std::string name;

}skills[] = {
	{ 	sf::Keyboard::Space, 	sf::Mouse::Left,		"slash"			},
	{ 	sf::Keyboard::Right, 	sf::Mouse::Right,		"cast_spell"	},
	{ 	sf::Keyboard::F,		sf::Mouse::XButton1,	"shoot_arrow"	},
	{ 	sf::Keyboard::Down, 	sf::Mouse::XButton2,	"poke"			}
=======
	{ sf::Keyboard::Down,	"walk_down",	 0, +2 }
>>>>>>> level_editor_with_sql
};

sf::Vector2f Vector2f_from_Vector2i(sf::Vector2i vector);

<<<<<<< HEAD
std::string get_skill_from_button_keys();
=======

>>>>>>> level_editor_with_sql
sf::Vector2f get_move_direction_from_button_keys();
std::string get_action_name_from_button_keys();
sf::Vector2f get_mouse_position(sf::RenderWindow & window);
bool check_mouse();


