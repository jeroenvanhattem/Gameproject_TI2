#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Layout{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int spriteSize = 32;
	sf::RenderWindow & window;
	sf::Vector2f windowSize = window.getView().getSize();

	char *grass = "tiles/grass.png";
public:
	Layout(sf::RenderWindow & window);
	int get_tile();
	void set_grid_layout();
	~Layout();
};

