#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "screen_objects.hpp"


class rectangle : public screen_objects {
private:
	sf::Vector2f position;
	sf::Vector2f end_position;
	sf::Vector2f size = position - end_position;
	sf::RectangleShape square;
	sf::Color color;
	bool selected = false;


public:
	rectangle(sf::Vector2f position = {10, 10}, sf::Color color = sf::Color::White, sf::Vector2f end_position = { 20,20 });
	void draw(sf::RenderWindow & window) const override;
	void move(sf::Vector2f delta);
	sf::FloatRect get_bounds();
	std::string to_string();
	void is_selected();
	bool check_selected();
	void cancel_selected();
};

