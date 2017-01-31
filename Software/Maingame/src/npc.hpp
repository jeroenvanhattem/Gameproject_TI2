#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "ability.hpp"
#include "sql.hpp"


class npc{
private:
	std::vector<ability*>npc_actions;
	std::vector<std::string>npc_values;
	std::string id;
	sf::Vector2f position;
	
	/*
	0) name
	1) sprite_id
	2) map
	3) level
	4) pos_x
	5) pos_y
	6) faction_id
	*/
	sql & database;

	int sprite_size = 64;
	sf::Texture texture;
	sf::RenderWindow & window;
	std::string current_action = "walk_down";
	
	

	const std::vector<std::string>action_names = {
		"cast_spell_up",
		"cast_spell_left",
		"cast_spell_down",
		"cast_spell_right",
		"poke_up",
		"poke_left",
		"poke_down",
		"poke_right",
		"walk_up",
		"walk_left",
		"walk_down",
		"walk_right",
		"slash_up",
		"slash_left",
		"slash_down",
		"slash_right",
		"shoot_arrow_up",
		"shoot_arrow_left",
		"shoot_arrow_down",
		"shoot_arrow_right",
		"die"
	};

	bool is_player = false;

	void load_all_actions();
	void load_action(std::string action_name, int steps_of_action, int level);


	
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
	/// npc_id : sf::string \n
	///	-> id of the npc that has to be drawn.
	/// 
	/// is_player : bool \n
	///	-> boolean to select if this npc is the player or not.
	/// 
	///
	/// Example:
	/// --------
	/// ability a(window, database, "1")\n
	///
	npc(sf::RenderWindow & window, sql & database, std::string npc_id, bool is_player = false);
	
	
	/// Move the npc
	//
	/// This method moves the position an npc.\n
	///
	///
	/// Parameters:
	/// -------
	/// delta : sf::Vector2f\n
	/// -> new position of the npc.
	///
	///
	/// Example:
	/// --------
	/// move({2,0})\n
	/// npc has moved 2 pixels to the right\n
	///
	void move(sf::Vector2f delta);
	
	
	/// set action of npc
	//
	/// This method sets the current action of the npc.\n
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
	/// npc is now set for walking up.\n
	///
	void set_action(std::string s = "0");
	
	
	/// Get the name of npc
	//
	/// This method returns the name of an npc.\n
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
	/// "monk"\n
	///
	std::string get_name();
	
	
	/// Print npc
	//
	/// This method draws the npc on the screen. \n
	///
	///
	const void draw();



	/// Get a sf::IntRect from the coordinates from the NPC
	//
	/// This function returns a sf::IntRect object which is created from the position and size of the NPC object\n
	/// 
	/// Return:
	/// -------
	/// intrect_object : sf::IntRect \n
	///	-> a sf::IntRect object using the position and size of the NPC object
	/// 
	/// Example:
	/// --------
	/// get_bounds() \n
	/// return: sf::IntRect(100, 100, 30, 30) .
	///
	sf::IntRect get_bounds();


	/// int npc::get_interaction(npc & other_npc) : Get interaction between two NPC's
	//
	/// Call the 'get_interaction' function to check for a collision with another NPC
	/// Do this by calling 'get_interaction()' with a NPC object as parameter


	///Get interaction between two NPC's
	//
	/// Call the 'get_interaction' function to check for a collision with another NPC
	/// 
	/// Parameters:
	/// -----------
	/// other_npc : NPC & \n
	///	-> Table name in the database
	///
	/// Return:
	/// -------
	/// 0 / 1 : integer \n
	///	-> Return a 1 if there's a collision detected, return a 0 if no collision is detected
	/// 
	/// Example:
	/// --------
	///player.get_interaction(*other_npc) \n
	/// return: {"1"}.
	///
	int get_interaction(npc & other_npc);

	int get_collision(sf::IntRect colliding_object);

	sf::Vector2f get_position() { return position; }
	void set_position(sf::Vector2f given_position);

	void show_action(std::string action_to_perform);


	/// Decontructor
	//
	/// Will be called when the object is deleted. \n
	/// 
	~npc();
};

