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
	/// npc_name : sf::string \n
	///	-> name of the npc that has to be drawn.
	/// 
	/// is_player : bool \n
	///	-> boolean to select if this npc is the player or not.
	/// 
	///
	/// Example:
	/// --------
	/// ability a("arno", {...}, {100,100})\n
	///
	npc(sf::RenderWindow & window, sql & database, std::string npc_name, bool is_player = false);
	
	
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


	/// Decontructor
	//
	/// Will be called when the object is deleted. \n
	/// 
	~npc();
};

