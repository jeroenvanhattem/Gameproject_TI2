#include "npc.hpp"

npc::npc(sf::RenderWindow & window, sql & database, std::string npc_id, bool is_player):
	window(window),
	database(database),
	id(npc_id)
{

	npc::is_player = is_player ? true : false;
	if (is_player) { 
		npc_values = database.get_player_value(npc_id); 
		
		position = { std::stof(npc_values.at(4)), std::stof(npc_values.at(5)) };
		texture.loadFromFile(npc_values.at(1));
	}
	else { 
		npc_values = database.get_npc_value(id); 
		position = { std::stof(npc_values.at(3)), std::stof(npc_values.at(4)) };

		
		texture.loadFromFile(npc_values.at(1));
	}
	
	texture.setSmooth(true);
	load_all_actions();
}

void npc::load_all_actions(){
	load_action("cast_spell_up",		7, 0);
	load_action("cast_spell_left",		7, 1);
	load_action("cast_spell_down",		7, 2);
	load_action("cast_spell_right",		7, 3);
	
	load_action("poke_up",				8, 4);
	load_action("poke_left",			8, 5);
	load_action("poke_down",			8, 6);
	load_action("poke_right",			8, 7);
	
	load_action("walk_up",				9, 8);
	load_action("walk_left",			9, 9);
	load_action("walk_down",			9, 10);
	load_action("walk_right",			9, 11);
	
	load_action("slash_up",				6, 12);
	load_action("slash_left",			6, 13);
	load_action("slash_down",			6, 14);
	load_action("slash_right",			6, 15);
	
	load_action("shoot_arrow_up",		13, 16);
	load_action("shoot_arrow_left",		13, 17);
	load_action("shoot_arrow_down",		13, 18);
	load_action("shoot_arrow_right",	13, 19);
	
	load_action("die",					6, 20);
}

void npc::move(sf::Vector2f delta) {
	position += delta;
	for (auto action : npc_actions) {
		if (action->get_name() == current_action) {
			action->move(position);
		}
	}
}


void npc::load_action(std::string action_name, int steps_of_action, int level){
	
	std::vector<sf::Sprite>temp_list;
	sf::Sprite s;
	s.setTexture(texture);
	
	for (int x = 0; x < steps_of_action; x++) {
		s.setTextureRect( sf::IntRect( x*sprite_size, level*sprite_size, sprite_size, sprite_size) );
		temp_list.push_back(s);
	}
	
	npc_actions.push_back(new ability(action_name, temp_list, position));
}



void npc::set_action( std::string s ) {
	for (auto action : npc_actions) {
		if (s == action->get_name()) {
			current_action = s;
		}
	}
}

const void npc::draw() {
	for (auto action : npc_actions) {
		if (current_action == action->get_name()) {
			action->draw(window);
			return;
		}
	}
}

std::string npc::get_name() {
	return npc_values.at(0);
}


npc::~npc() {

}