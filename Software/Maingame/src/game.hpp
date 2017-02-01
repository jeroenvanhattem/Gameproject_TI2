#ifndef _game_HPP
#define _game_HPP

#include <SFML\Graphics.hpp>
#include <iostream>
#include "sqlite3.h"
#include "sql.hpp"
#include <functional>
#include "objects.hpp"
#include "dialogbox.hpp"
#include "button_actions.hpp"
#include "npc.hpp"
#include "player.hpp"
#include "leveleditor.hpp"

class game {
private:
	player arno;
	dialogbox dialogbox;
	sql & database;
	sf::RenderWindow & window;
	sf::View game_view;
	sf::Vector2f levelsize;
	std::vector<picture*> background_store;
	std::vector<npc*>npc_list;
	std::vector<sf::IntRect>collision_objects;
	std::vector<sf::IntRect>collision_backgrounds;
	std::map<std::string, std::vector<std::string>>background_values_map;
	std::map<std::string, std::vector<std::string>>object_values_map;

	/*std::string tutorial_sentence = "Welcome, try to walk using the up, down, left or right keys.\n\nPress space to begin!";
	std::string game_intro = "Ouch, where am i?\n\nIt feels like i slept for hours and i can't remember a thing.\n\n[press space to continue])";
	std::string trigger_1 = "Wow, did you do that all by yourself? .... Idiot.";*/
	
	bool game_begin = false;
	bool first_dialog_done = false;
	int count = 0;


	/// void draw_npc() : This function will draw NPC's on the window
	//
	/// This function will go through a vector which contains NPC objects, their draw function will be called on all of them one by one
	/// Example:
	/// --------
	/// draw_npc() \n
	/// -> Drawing the NPC's on the window
	///
	void draw_npc();

	/// void load_npc() : This function will get all the NPC's from the database and put them in a vector
	//
	/// This function will retrieve all the NPC's from the database and put them in the 'npc_list' vector
	/// Example:
	/// --------
	/// load_npc() \n
	/// -> The npc_list vector will be filled with NPC objects from the database
	///
	void load_npc();

	/// void view_start_dialogs() : This function shows the dialogues in the beginning of the game
	//
	/// This function shows the the dialogs that will be shown in the beginning of the game
	/// Example:
	/// --------
	/// view_start_dialogs() \n
	/// -> Dialogues will be shown on the bottom of the screen
	///
	void view_start_dialogs();

	/// void draw_background_store() : This function shows the store on the window
	//
	/// This function retrieves the background of the store from the vector it's in and displays it on the screen
	/// Example:
	/// --------
	/// draw_background_store() \n
	/// -> The store will be shown on the window
	void draw_background_store();

	/// void move_player() : This function moves the player if it meets the requirements to move
	//
	/// This function will move the player as long as there's no collision. When there's a collision the player will be set back to its previous position before the collision
	/// Example:
	/// --------
	/// move_player() \n
	/// -> Move the player
	void move_player();

	/// void draw_player() : This function draws the player on the screen
	//
	/// This function calls the draw function from the 'player' class, which will then draw the player on the screen
	/// Example:
	/// --------
	/// move_player() \n
	/// -> Player will be shown on the screen
	void draw_player();

	/// void perform_player_action(std::string action) : This function show the sprite that belongs to the action
	//
	/// This function shows the action the belongs to the state of the player, if he walks up, the sprite will be shown of the player walking up
	/// 
	/// Parameters:
	/// -----------
	/// action : std::string
	///	-> The name of the action that must be performed
	///
	/// Example:
	/// --------
	/// perform_player_action("walk_up") \n
	/// - > The player will be shown doing something, like walking up, walking down or dying
	///
	void perform_player_action(std::string action);

	/// void perform_npc_action(std::string npc_name,std::string action) : This function show the sprite that belongs to the action
	//
	/// This function shows the action the belongs to the state of the NPC, if it walks up, the sprite will be shown of the NPC walking up
	/// 
	/// Parameters:
	/// -----------
	/// action : std::string
	///	-> The name of the action that must be performed
	/// npc_name : std::string
	///	-> The name of the NPC on which this function must be executed
	///
	/// Example:
	/// --------
	/// perform_npc_action("henk", "walk_up") \n
	/// - > The NPC will be shown doing something, like walking up, walking down or dying
	///
	void perform_npc_action(std::string npc_name, std::string action);

	/// void interact() : Make the player, when possible, interact with a NPC
	//
	/// Call the 'interact' function to see if the player can interact with a player
	/// Example:
	/// --------
	/// player.interact() \n
	/// -> Executing the function which will show text on the screen
	///
	void interact();

	/// void interact(std::string item_id) : Make the player, when possible, interact with a NPC
	//
	/// Call the 'interact' function to see if the player can interact with a player
	/// 
	/// Parameters:
	/// -----------
	/// item_name : std::string
	///	-> The name of an item which will be given to the player
	///
	/// Example:
	/// --------
	/// player.interact("banana") \n
	/// - > Give the player an item and update this in the database
	///
	void interact(std::string item_id);

public:

	/// game(sf::RenderWindow & window, sql & database, sf::Vector2f levelsize) : The constructor of a the 'game' class
	//
	/// The constructor of the 'game' class, this creates a game object
	/// 
	/// Parameters:
	/// -----------
	/// levelsize :  sf::Vector2f
	///	-> The size of the level
	/// database : sql &
	///	-> A 'SQ' object, this will be used to get information from the database
	/// window :sf::RenderWindow
	///	-> The window on which the game has to be drawn
	///
	/// Example:
	/// --------
	/// game(window, database, levelsize) \n
	/// - > This will create a 'game' object
	///
	game(sf::RenderWindow & window, sql & database, sf::Vector2f levelsize);

	/// game_loop() : This function is the game loop, when called it will play the game
	//
	/// This funtion will execute everything that will be needed to run the game, like drawing the window, loading the NPC's and working with them
	/// 
	/// Example:
	/// --------
	/// game_loop() \n
	/// - > This will start the game
	///
	void game_loop();

	/// get_items_from_database(std::map<std::string, std::vector<std::string>> & item_values_map) : This function gets the items from the database
	//
	/// This function gets all the items from the database and places it in a std::map
	/// 
	/// Parameters:
	/// -----------
	/// item_values_map :  std::map<std::string, std::vector<std::string>> & 
	///	-> The map that contains all the items and its location
	///
	/// Example:
	/// --------
	/// get_items_from_database(background_values_map) \n
	/// - > The std::map will be filled with the items
	///
	void get_items_from_database(std::map<std::string, std::vector<std::string>> & item_values_map);
};

#endif
