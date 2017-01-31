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
	if(position != new_position){
		position = new_position;

		for (auto & item : action) {
			item.setPosition(position);
		}
		
		if (current_action_step < int(action.size()) - 1) {
			current_action_step++;
		}
		else {
			current_action_step = 0;
		}
	}
	else {
		current_action_step = 0;
	}
	
}


const void ability::draw(sf::RenderWindow & window) {
	window.draw(action.at(current_action_step));
}

void ability::add_sprite_to_action(sf::Sprite t) {
	action.push_back(t);
}

void ability::perfrom_action(sf::RenderWindow & window) {
	sf::View ability;
	window.setView(ability);
	
	for (auto & indexer : action) {
		window.clear();
		window.draw(indexer);
		window.display();
		sf::sleep(sf::milliseconds(200));
	}
	window.setView(window.getDefaultView());
}


ability::~ability(){
}
