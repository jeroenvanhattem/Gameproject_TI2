#pragma once
#include "sqlite3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <SFML\Graphics.hpp>

static std::vector<std::string> result;


class sql {
private:
	sqlite3 *database;
	std::string database_path = "../../bin/database.db";

	int rc;
	int connection;

	char* _ERROR_MESSAGE = 0;
	const char* data = "Callback function called";
	
	
	/// Checks if query is executed correctly.
	//
	/// This method checks if the executed query is correctly procesed.\n
	/// If that is not the case this function will print an error on the command prompt.\n
	/// 
	///
	/// Example:
	/// --------
	/// check_query_request()\n
	/// *no error, so do nothing*
	///
	void sql::check_query_request();

public:

	sql();
	~sql();

	/// Get data from a column in a table in the database.
	//
	/// This method gets the data from a column in a table in the database.\n
	/// 
	/// Parameters:
	/// -----------
	/// table : char* \n
	///	-> Table name in the database
	///
	/// column : char* \n
	///	-> Column name in the database
	///
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	/// Example:
	/// --------
	/// Get_data("player", "level") \n
	/// return: {"1"}.
	///
	std::vector<std::string> get_data(char* table, char* columnname);
	
	
	/// Get data from a column in a table in the database with condition.
	//
	/// This method gets the data from a table in the database,\n
	/// where the value of the given column meets the condition values.
	/// 
	/// Parameters:
	/// -----------
	/// table : char* \n
	///	-> Table name in the database
	///
	/// column : char* \n
	///	-> Column name in the database
	/// 
	/// condition1 : char* \n
	///	-> First condition of the Where statement in the SQL query.
	///
	/// condition2 : char* \n
	///	-> Second condition of the Where statement in the SQL query.
	///
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	/// Example:
	/// --------
	/// Get_data("player", "name","id","1") \n
	/// return: {"arno"}.
	///
	std::vector<std::string> get_data(char* table, char* columnname, char* condition1, char* condition2);
	
	
	/// Change values in the database.
	//
	/// This method overwrites data in the database,
	/// where the value of the given column meets the condition values.
	/// 
	/// Parameters:
	/// -----------
	/// table : char* \n
	///	-> Table name in the database
	///
	/// condition1 : char* \n
	///	-> First condition of the Where statement in the SQL query.
	/// 
	/// condition2 : char* \n
	///	-> Second condition of the Where statement in the SQL query.
	///
	/// columnname : char* \n
	///	-> Column name in the database
	///
	/// new_value : char* \n
	///	-> New value to be set in the specified column value
	/// 
	/// Example:
	/// --------
	/// change_data("player","id","1","name","pieter")\n
	/// The name of the player is now "pieter" instead of "arno"
	///
	void change_data(char* table, char* condition1, char* condition2, char* columnname, char* new_value);
	
	
	/// Add a new value to database.
	//
	/// This method adds a new value in the given table of the database.\n
	/// The parameter "value" is consists all the column values except the id,\n
	/// because the this value has auto increment.
	/// 
	/// Parameters:
	/// -----------
	/// table : char* \n
	///	-> Table name in the database
	///
	/// values : char* \n
	///	-> column values to add in the database.
	/// 
	/// 
	/// Example:
	/// --------
	/// add_data("sprites","'../../bin/objects/new_pic.png', new pic , 64 , 64")\n
	/// There is now a new record in the database with the given values.
	///
	void add_data(char* table, const char* values);
	
	
	/// Execute a query.
	//
	/// This method executes a given query that has no return value.\n
	/// 
	/// Parameters:
	/// -----------
	/// to_be_executed : const char* \n
	///	-> Query to be executed
	///
	/// 
	/// Example:
	/// --------
	/// execute_query_without_return("INSERT INTO sprites VALUES(NULL, '../../bin/objects/new_pic.png', new pic , 64 , 64);")\n
	/// There is now a new record in the database with the given values.
	///
	void execute_query_without_return(const char* to_be_executed);
	
	
	/// Execute a query.
	//
	/// This method executes a given query that has a return value.\n
	/// 
	/// Parameters:
	/// -----------
	/// to_be_executed : const char* \n
	///	-> Query to be executed
	///
	///
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	/// 
	/// Example:
	/// --------
	/// execute_query_with_return("SELECT name FROM player WHERE id == 1;")\n
	/// Return: {"arno"}
	///
	std::vector<std::string> execute_query_with_return(const char* to_be_executed);

	
	/// Get saved result.
	//
	/// This method returns the result that is stored in the global result value.\n
	/// the result value is a global and static because it is set by the callback function.\n
	/// 
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	/// 
	/// Example:
	/// --------
	/// get_result()\n
	/// Return: {"arno"}
	///
	static std::vector<std::string> get_result();
	
	
	/// Save result to static value.
	//
	/// This method adds a new value, what is a result of an query,\n
	/// to the static string vector result.\n
	/// It does not overwrite it because there could be a result of multiple strings.\n
	/// This function is only called by the static callback function.\n
	/// 
	/// Parameters:
	/// -----------
	/// x : char* \n
	///	-> Query result to add
	///
	/// 
	/// Example:
	/// --------
	/// set_result("arno")\n
	/// Last value in result is now "arno".
	///
	static void set_result(char* x) { result.push_back(x); }
	
	  /*------------------*/
	 /*  query functions */
	/*------------------*/
	/// Get value of column from the player
	//
	/// This method returns a column value of the player.\n
	/// The save is equal the the player id in the database,\n
	/// this is because the player can have multiple saved games.\n
	/// 
	/// Parameters:
	/// -----------
	/// save : int \n
	///	-> Save of the player and player id in the database
	///
	/// variable_name : std::string \n
	///	-> Columnname from what the value is requested.
	/// 
	/// 
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	///
	/// Example:
	/// --------
	/// get_player_value(1,"name")\n
	/// return: {"arno"}
	///
	std::vector<std::string> get_player_value(int save, std::string variable_name);
	
	
	/// Get sprite sheet of the player
	//
	/// This method returns the sprite sheet of the player.\n
	/// The save is equal the the player id in the database,\n
	/// this is because the player can have multiple saved games.\n
	/// 
	/// Parameters:
	/// -----------
	/// save : int \n
	///	-> Save of the player and player id in the database.
	/// 
	/// 
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	///
	/// Example:
	/// --------
	/// get_player_sprite(1)\n
	/// return: {"../../bin/sprite_sheets/player_sprite.png"}
	///
	std::vector<std::string> get_player_sprite(int save);
	
	
	  /*---------------*/
	 /* npc functions */
	/*---------------*/
	/// Get all values from columns in NPC
	//
	/// This method returns all column values of a NPC.\n
	///
	/// The order of the returning values in the vector is:\n
	///
	/// index	|	name of value \n
	/// ------------------------- \n
	///		0	|		name \n
	///		1	|		level \n
	///		2	|		class_id \n
	///		3	|		sprite_id \n
	///		4	|		position_x \n
	///		5	|		position_y \n
	///		6	|		quest_id \n
	/// 
	/// Parameters:
	/// -----------
	/// npc_id : std::string \n
	///	-> ID of the NPC from whom the values are asked.
	/// 
	/// 
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	///
	/// Example:
	/// --------
	/// get_npc_value("1")\n
	/// return: {"arno"}
	///
	std::vector<std::string> get_npc_value(std::string npc_id);
	
	
	/// Get all id's of the NPC's
	//
	/// This method returns all id values of the NPC table.\n
	/// The lengths of the vector is equal to how many NPC's there are in the table.\n
	/// 
	///
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	///
	/// Example:
	/// --------
	/// get_number_of_npcs()\n
	/// return: {"1","2","5"}
	///
	std::vector<std::string> get_number_of_npcs();
	
	  /*----------------*/
	 /*object functions*/
	/*----------------*/
	
	/// Get id's from objects and tiles sprites
	//
	/// This method returns all sprite id values of tiles and objects.\n
	/// 
	///
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	///
	/// Example:
	/// --------
	/// get_object_sprite_ids()\n
	/// return: {"1","2","5"}
	///
	std::vector<std::string> get_object_sprite_ids();
	
	
	/// Get all values from columns in sprites
	//
	/// This method returns all column values of a a sprite.\n
	/// The order of the returning values in the vector is:\n
	///
	/// index	|	name of value \n
	/// ------------------------- \n
	///		0	|		path \n
	///		1	|		name \n
	///		2	|		sprite_size_x \n
	///		3	|		sprite_size_y \n
	/// 
	/// 
	/// Parameters:
	/// -----------
	/// object_id : std::string \n
	///	-> ID of the object/tile from what the values are asked.
	/// 
	/// 
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	///
	/// Example:
	/// --------
	/// get_object_sprite_value("1")\n
	/// return: {"../../bin/objects/road1.png", "road1","32","32"}
	///
	std::vector<std::string> get_object_sprite_value(std::string object_id);
	


	  /*--------------------------------*/
	 /*  Saving background functions   */
	/*--------------------------------*/


	/// Create new map.
	//
	/// This method creates a new record in the maps table.\n
	/// This record consists the map_id, 
	/// map name and the corresponding background music.\n
	///
	/// 
	/// Parameters:
	/// -----------
	/// map_name : std::string \n
	///	-> name of the level that has to be created.
	/// 
	/// background_music : int \n
	///	-> id of the background music of the level.
	/// 
	///
	/// Example:
	/// --------
	/// set_new_map("level1",1)\n
	/// There is now a new maps record in the database,\n
	/// that has the name level1 with brackground_id 1.\n
	///
	void set_new_map(std::string map_name, int background_music);
	


	/// Saves the tiles in the database.
	//
	/// This method saves a tile in the database.\n
	/// The tile values will be filterd if it is an object or an background tile.\n
	/// It is very importend that if you want to save the level, that the map_name is spelled correctly.\n
	/// If the map_name is not correctly spelled or if it doesn't exist, the level cannot be saved. \n
	/// The same counts for the tile path.
	///
	/// 
	/// Parameters:
	/// -----------
	/// tile_path : std::string \n
	///	-> path to the consisting image of the object/tile.
	/// 
	/// pos_x : int \n
	///	-> x position where the object/tile should be placed in the map.
	/// 
	/// pos_y : int \n
	///	-> y position where the object/tile should be placed in the map.
	/// 
	/// map_name : std::string \n
	///	-> name of the map where the object/tile will be placed in.
	/// 
	///
	/// Example:
	/// --------
	/// save_tiles("../../bin/objects/example.png",10,10,"level1")\n
	/// This object is now saved in the objects table, \n
	/// with a refference that is has to be placed in level1.\n
	///
	void save_tiles(std::string tile_path, int pos_x, int pos_y, std::string map_name);



	/// Get the names of all levels in the database.
	//
	/// This method returns all names of the levels that are in the database.\n
	/// This can be usefull so you can know if a level already exists.
	/// 
	///
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	///
	/// Example:
	/// --------
	/// get_available_levels()\n
	/// return: {"level1","level2","level5"}
	///
	std::vector<std::string> get_available_levels();


	/// Get the ID's of all levels in the database.
	//
	/// This method returns all ID's of the levels that are in the database.\n
	/// 
	///
	/// Return:
	/// -------
	/// list_of_data : std::vector<std::string> \n
	///	-> List that contains the asked data in the form of strings.
	/// 
	///
	/// Example:
	/// --------
	/// get_level_ids()\n
	/// return: {"1","2","5"}
	///
	std::vector<std::string> get_level_ids();


	/// Get all object values of a level.
	//
	/// This method returns the values of all objects that are assigned to the given level ID.\n
	/// IMPORTANT!: In the next patch this function will be merged in a new function together with get_level_background_value(std::string level_id).\n
	/// 
	/// 
	/// Parameters:
	/// -----------
	/// level_id : std::string \n
	///	-> id of the level from what the objects have to be loaded.
	/// 
	///
	/// Return:
	/// -------
	/// list_of_data : std::map<std::string, std::vector<std::string>> \n
	///	-> map that contains the asked data in the form of strings with name as key.\n
	/// 
	///
	/// Example:
	/// --------
	/// get_level_object_value("level1")\n
	/// return: {"road1":{"../../bin/objects/example.png","120","150","1"}}
	///
	std::map<std::string, std::vector<std::string>> get_level_object_value(std::string level_id);


	/// Get all background values of a level.
	//
	/// This method returns the values of all background tiles that are assigned to the given level ID.\n
	/// IMPORTANT!: In the next patch this function will be merged in a new function together with get_level_object_value(std::string level_id).
	/// 
	/// 
	/// Parameters:
	/// -----------
	/// level_id : std::string \n
	///	-> id of the level from what the background tiles have to be loaded.
	/// 
	///
	/// Return:
	/// -------
	/// list_of_data : std::map<std::string, std::vector<std::string>> \n
	///	-> map that contains the asked data in the form of strings with name as key.\n
	/// 
	///
	/// Example:
	/// --------
	/// get_level_object_value("level1")\n
	/// return: {"road1":{"../../bin/tiles/example.png","120","150","1"}}
	///
	std::map<std::string, std::vector<std::string>> get_level_background_value(std::string level_id);


	  /*-------------------*/
	 /*  Player functions */
	/*-------------------*/

	std::vector<std::string> get_player_value(std::string npc_id);



	  /*-------------------*/
	 /*  Music functions  */
	/*-------------------*/

	std::vector<std::string> get_music(std::string map_id);

	
	/// Get value from database
	//
	/// This method is used to get the value from the database.
	/// What the function does is explained in the sqlite3.hpp file.
	/// In this class we use it to store the found data in a global static value.
	///
	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};