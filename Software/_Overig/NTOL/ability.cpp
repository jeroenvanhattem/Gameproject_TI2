#include "ability.hpp"



ability::ability(std::string name, std::vector<sf::Sprite> & action_list, sf::Vector2f position):
	name(name),
	position(position)
{
	for (auto item : action_list) {
		item.setPosition(position);
		action.push_back(item);
	}
}

std::string ability::get_name() {
	return name;
}

void ability::move( sf::Vector2f new_position) {
	position = new_position;

	for (auto & item : action) {
		
		item.setPosition(position);
		
	}
}

void ability::set_action(std::string s) {

}

const void ability::draw(sf::RenderWindow & window) {
	window.draw(action.at(current_action_step));
		
	if (current_action_step < int(action.size()) - 1) {
		current_action_step++;
	}
	else {
		current_action_step = 0;
	}
		
	
}

void ability::add_sprite_to_action(sf::Sprite t) {
	action.push_back(t);
}



ability::~ability()
{
}
