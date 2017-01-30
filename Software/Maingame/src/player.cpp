#include "player.hpp"



player::player(sf::RenderWindow & window, sql & database, std::string save) :
	player_npc(window, database, save, true),
	database(database),
	player_id(save)
{
	player_npc.draw();
	spawn = { 
		std::stof(database.get_player_value(player_id).at(4)), 
		std::stof(database.get_player_value(player_id).at(5)) 
	};
}

void player::move(sf::Vector2f delta) {
	player_npc.move(delta);
	last_move = delta;
	position += delta;
}

void player::set_action(std::string s) {
	player_npc.set_action(s);
}

void player::draw() {
	
	for (auto i : database.get_player_value(player_id)) {
		std::cout << i << "\t";
	}
	std::cout << "\n";
	player_npc.draw();
}

void player::set_last_position() {
	position -= last_move;
	player_npc.set_position(position);
}

void player::respawn() {
	player_npc.set_position(spawn);
}

int player::get_interaction(npc & other_npc) {
	return player_npc.get_interaction(other_npc);
}

sf::Vector2f player::get_position() {
	return player_npc.get_position();
}


player::~player()
{
}
