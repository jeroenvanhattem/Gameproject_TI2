#include "player.hpp"



player::player(sf::RenderWindow & window, sql & database, std::string save):
	player_npc(window, database, save, true)
{
	player_npc.draw();
}

void player::move(sf::Vector2f delta) {
	player_npc.move(delta);
}
void player::set_action(std::string s) {
	player_npc.set_action(s);
}
void player::draw() {
	player_npc.draw();
}


player::~player()
{
}
