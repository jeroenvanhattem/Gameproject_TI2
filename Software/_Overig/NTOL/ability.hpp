#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <ctime>


class ability{
private:
	std::string name;
	std::vector<sf::Sprite>action;
	sf::Vector2f position;
	int current_action_step = 0;
	

public:
	ability(std::string name, std::vector<sf::Sprite> & action, sf::Vector2f position);
	std::string get_name();
	void move( sf::Vector2f new_position);
	void set_action(std::string s);
	const void draw(sf::RenderWindow & window);
	void add_sprite_to_action(sf::Sprite t);
	~ability();
};

