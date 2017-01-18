#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class player{
private:
	//lopen is op y niveau 9-12		aantal stappen: 9
	std::vector<sf::Texture>move_up;
	std::vector<sf::Texture>move_left;
	std::vector<sf::Texture>move_down;
	std::vector<sf::Texture>move_right;
	std::vector<sf::Texture>cast_down;
	int move_action = 0;
	sf::Texture texture;
	std::string sprite_sheet;
	sf::Sprite sprite;
	int spriteSize = 64;
	
public:
	player(std::string sprite_sheet);
	void load_action(std::vector<sf::Texture> & action, int steps, int level_in_sprite);
	void draw(sf::RenderWindow & window);
	void move(sf::Vector2f delta);
	~player();
};

