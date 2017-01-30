#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>


class ability{
private:
	std::string name;
	std::vector<sf::Sprite>action;
	sf::Vector2f position;
	int current_action_step = 0;
	

public:

	/// Constructor
	//
	/// This method will crate an object of class ability.\n
	///
	/// 
	/// Parameters:
	/// -----------
	/// name : std::string \n
	///	-> name of the ability to be loaded.
	///
	/// action : std::vector<sf::Sprite> \n
	///	-> list of sprites that the animation of the ability needs.\n
	///
	/// position : sf::Vector2f \n
	///	-> position of the player, so the ability is loaded on that spot.
	/// 
	///
	/// Example:
	/// --------
	/// ability a("arno", {...}, {100,100})\n
	///
	ability(std::string name, std::vector<sf::Sprite> & action, sf::Vector2f position);


	/// Get the name of ability
	//
	/// This method returns the name of an ability.\n
	///
	///
	/// Return:
	/// -------
	/// name : std::String\n
	/// -> name of the ability
	///
	///
	/// Example:
	/// --------
	/// get_name()\n
	/// "walk_up"\n
	///
	std::string get_name();


	/// Move the current ability
	//
	/// This method moves the position of the ability, \n
	/// so that the ability sprite is printed on the right position.\n
	///
	///
	/// Parameters:
	/// -------
	/// new_position : sf::Vector2f\n
	/// -> new position of the ability sprite
	///
	///
	/// Example:
	/// --------
	/// move({200,200})\n
	/// ability position now set on 200, 200\n
	///
	void move( sf::Vector2f new_position);


	/// Print ability
	//
	/// This method draws the ability on the screen. \n
	///
	///
	/// Parameters:
	/// -------
	/// window : sf::RenderWindow\n
	/// -> window where the ability have to be drawn on.\n
	///
	const void draw(sf::RenderWindow & window);


	/// Add a sprite to the action
	//
	/// This method will add a new sprite to the action. \n
	/// It can be used if the ability needs an extra sprite that is not loaded.\n
	///
	///
	/// Parameters:
	/// -------
	/// t : sf::Sprite\n
	/// -> new sprite that will be added to the ability.
	///
	///
	/// Example:
	/// --------
	/// add_sprite_to_action(example_sprite)\n
	///
	void add_sprite_to_action(sf::Sprite t);


	/// Decontructor
	//
	/// Will be called when the object is deleted. \n
	/// 
	~ability();
};

