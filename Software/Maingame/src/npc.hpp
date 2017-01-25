#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "ability.hpp"


class npc{
private:
	std::vector<ability*>npc_actions;
	int sprite_size = 64;
	sf::Texture texture;
	sf::Vector2f position;
	sf::RenderWindow & window;
	std::string current_action = "walk_up";
	
	

	const std::vector<std::string>action_names = {
		"cast_spell_up",
		"cast_spell_left",
		"cast_spell_down",
		"cast_spell_right",
		"poke_up",
		"poke_left",
		"poke_down",
		"poke_right",
		"walk_up",
		"walk_left",
		"walk_down",
		"walk_right",
		"slash_up",
		"slash_left",
		"slash_down",
		"slash_right",
		"shoot_arrow_up",
		"shoot_arrow_left",
		"shoot_arrow_down",
		"shoot_arrow_right",
		"die"
	};

	bool is_player = false;

	void load_all_actions();
	void load_action(std::string action_name, int steps_of_action, int level);


	
public:
	npc(sf::RenderWindow & window, std::string sprite_path, sf::Vector2f position, bool is_player = false);
	void move_player(sf::Vector2f delta);
	void set_action(std::string s = "0");
	const void draw();
	~npc();
};

