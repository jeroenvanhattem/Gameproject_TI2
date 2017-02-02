#pragma once

#include "item.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "sql.hpp"


class inventory {
private:
	sf::RenderWindow & window;
	sql & database;
	std::vector<item> inventory_vector;


	int counter = 1;

	sf::Sprite inventory_sprite;
	sf::Texture inventory_texture;

public:
	inventory(sf::RenderWindow & window, sql & database);

	/// void get_inventory() : Get the inventory
	//
	/// This function returns the items in the inventory
	/// 
	/// Example:
	/// --------
	/// get_inventory(1) \n
	/// -> Shows the items in the inventory
	///
	void get_inventory();
};