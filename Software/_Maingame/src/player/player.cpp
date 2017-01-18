#include "player.hpp"



player::player(std::string sprite_sheet):
	sprite_sheet(sprite_sheet)
{
	load_action(move_up,	9, 8 );
	load_action(move_left,	9, 9 );
	load_action(move_down,	9, 10);
	load_action(move_right, 9, 11);

	sprite.setPosition(200, 200);
	sprite.setTexture(move_up[0]);
}

void player::load_action(std::vector<sf::Texture> & action, int steps, int level_in_sprite) {
	for (int sprite_action_steps = 0; sprite_action_steps < steps * spriteSize; sprite_action_steps += spriteSize) {
		texture.loadFromFile(sprite_sheet, sf::IntRect(sprite_action_steps, level_in_sprite * spriteSize, spriteSize, spriteSize));
		texture.setSmooth(true);
		action.push_back(texture);
	}

}

void player::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}


void player::move(sf::Vector2f delta){
	if (delta.x >0) {
		sprite.setTexture(move_right[move_action]);
	}
	else if(delta.x<0){
		sprite.setTexture(move_left[move_action]);
	}
	else if (delta.y>0) {
		sprite.setTexture(move_down[move_action]);
	}
	else if (delta.y<0) {
		sprite.setTexture(move_up[move_action]);
	}
	move_action++;
	if (move_action >= 9) {
		move_action = 1;
	}
	
	if (sprite.getPosition().x+spriteSize <= 512 && sprite.getPosition().y >= 0 && sprite.getPosition().x >=0 && sprite.getPosition().y+spriteSize <= 512) {
		sprite.setPosition(sprite.getPosition() + delta);
	}
	
	
}

player::~player(){
}


