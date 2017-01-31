#pragma once

#include <iostream>
#include <npc.hpp>


class player{
private:
	npc player_npc;
	std::string player_id;
	sf::Vector2f spawn;
	sf::Vector2f position;
	sf::Vector2f last_move;
	sql database;
public:


	/// Constructor
	//
	/// This method will crate an object of class npc.\n
	///
	/// 
	/// Parameters:
	/// -----------
	/// window : sf::RenderWindow \n
	///	-> window where content will be drawn on.
	///
	/// database : sql \n
	///	-> referrence to the database class.\n
	///
	/// save : sf::string \n
	///	-> id of the current game save.
	/// 
	///
	/// Example:
	/// --------
	/// player a(window, database, "1")\n
	///
	player(sf::RenderWindow & window, sql & database, std::string save);


	/// Move the player
	//
	/// This method moves the position the player.\n
	///
	///
	/// Parameters:
	/// ------------
	/// delta : sf::Vector2f\n
	/// -> new position of the player.
	///
	///
	/// Example:
	/// --------
	/// move({2,0})\n
	/// player has moved 2 pixels to the right\n
	///
	void move(sf::Vector2f delta);


	/// Set action of the player
	//
	/// This method sets the current action of the player.\n
	/// The standard value is walk down.\n
	///
	///
	/// Parameters:
	/// -------
	/// s : std::string\n
	/// -> name of the action that has to be set on active.
	///
	///
	/// Example:
	/// --------
	/// set_action("walk_up")\n
	/// player is now set for walking up.\n
	///
	void set_action(std::string s);


	/// Print player
	//
	/// This method draws the player on the screen. \n
	///
	///
	void draw();

	void respawn();

	int get_interaction(npc & other_npc);

	int get_collision(sf::IntRect colliding_object);

	void set_last_position();

	sf::Vector2f get_position();

	
	void show_action(std::string action_to_perform);


	/// Decontructor
	//
	/// Will be called when the object is deleted. \n
	/// 
	~player();
};

