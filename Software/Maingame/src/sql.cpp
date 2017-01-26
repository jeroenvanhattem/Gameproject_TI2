#include "sql.hpp"

sql::sql() {
	//Checking if the given database exists and not locked.
	std::ifstream database_existance(database_path);
	if (!database_existance.good()) {
		std::cout	<< "Error: Could not open database."				//error definition
					<< "Probbably incorrect path or locked file.\n";	//error explanation
		while (1);
	}
	else { 
		std::cout << "Database correctly opened.\n";					//database found
	}
	database_existance.close();

	//Opening the database
	connection = sqlite3_open(database_path.c_str(), &database);
}
sql::~sql() {
	sqlite3_close(database);
}

int sql::callback(void *NotUsed, int argc, char **argv, char **azColName) {
	for (int i = 0; i < argc; i++) {
		set_result(argv[0]);
	}
	return 0;
}

void sql::check_query_request() {
	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE << "\tLine: " << __LINE__ << std::endl;
		sqlite3_free(_ERROR_MESSAGE);
	}
}

void sql::execute_query_without_return(const char* to_be_executed) {
	while (rc = sqlite3_exec(database, to_be_executed, callback, 0, &_ERROR_MESSAGE) != 0);
	check_query_request();
}

std::vector<std::string> sql::execute_query_with_return(const char* to_be_executed) {

	while (rc = sqlite3_exec(database, to_be_executed, callback, 0, &_ERROR_MESSAGE) != 0);
	check_query_request();

	return get_result();
}


std::vector<std::string> sql::get_data(char* table, char* columnname, char* condition1, char* condition2) {
	std::ostringstream query;
	query << "SELECT " << columnname << " FROM " << table << " WHERE " << condition1 << " == " << condition2 << ";";
	
	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}


std::vector<std::string> sql::get_data(char* table, char* columnname) {
	std::ostringstream query;
	query << "SELECT " << columnname << " FROM " << table << ";";
	
	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}



void sql::add_data(char* table, char* values) {
	std::ostringstream query;
	query << "INSERT INTO " << table << " VALUES( NULL, " << values << ");";

	std::string query_string = query.str();
	//rc = sqlite3_exec(database, query_string.c_str(), callback, 0, &_ERROR_MESSAGE);
	execute_query_without_return(query_string.c_str());
}

void sql::change_data(char* table, char* condition1, char* condition2, char* value1, char* value2) {
	std::ostringstream query;
	query	<< "UPDATE "	<< table 
			<< " SET "		<< value1		<< " = '"	<< value2 
			<< "' WHERE "	<< condition1	<< " = "	<< condition2 << ";";
	
	std::string query_string = query.str();
	execute_query_without_return(query_string.c_str());
}

std::vector<std::string> sql::get_result() {
	std::vector<std::string>temp_result_save;
	temp_result_save = result;
	while (result.size() > 0) {
		result.pop_back();
	}
	return temp_result_save;

}



std::vector<std::string> sql::get_player_value(int save, std::string variable_name) {
	std::ostringstream query;
	query	<< "SELECT " << variable_name
			<< " FROM player "
			<< "WHERE id == " << save << ";";

	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}


std::vector<std::string> sql::get_player_sprite(int save) {
	std::ostringstream query;
	query	<< "SELECT sprites.path "
			<< "FROM sprites, player "
			<< "WHERE sprites.id = player.sprite_id "
			<< "AND name = " << save << ";";

	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}






std::vector<std::string> sql::get_number_of_npcs() {
	std::vector<std::string>total = get_data("NPC", "id");
	return total;
}

std::vector<std::string> sql::get_npc_value(std::string npc_id) {
	/*
	This function searches all npc variables in the database

	return:
	--------
	list of lists of npc variables: std::vector<std::vector<std::string>>
	
	returning npc variables order:
	------------------------
	0) name
	1) sprite
	2) level
	3) class
	4) position
	5) quest

	*/
	std::vector<std::string>temp_npc_value;
	std::vector<std::string>npc_values;
	std::string temp_query_string;
	std::ostringstream ostring_query;

	ostring_query 
	<< "SELECT "<< "name"			
	<< " FROM "	<< "NPC"		
	<< " WHERE "<< "id"	<< " == " << npc_id << ";"
	
	<< "SELECT "<< "sprites.path"	
	<< " FROM "	<< "sprites, NPC"
	<< " WHERE "<< "sprites.id"	<< " == " << "sprites.id" 
	<< " AND "	<< "NPC.id"		<< " == " << npc_id << ";"
	
	<< "SELECT " << "class_id"		
	<< " FROM "	 << "NPC"		
	<< " WHERE " << "id" << " == " << npc_id << ";"

	<< "SELECT " << "position_x"	
	<< " FROM "  << "NPC"		
	<< " WHERE " << "id" << " == " << npc_id << ";"
	
	<< "SELECT " << "position_y"	
	<< " FROM "  << "NPC"		
	<< " WHERE " << "id" << " == " << npc_id << ";"
	
	<< "SELECT " << "quest_id"		
	<< " FROM "  << "NPC"		
	<< " WHERE " << "id" << " == " << npc_id << ";";

	temp_query_string = ostring_query.str();
	temp_npc_value = execute_query_with_return(temp_query_string.c_str());
	for (auto indexer : temp_npc_value) {
		npc_values.push_back(indexer);
	}
	
	return npc_values;
}


std::vector<std::string> sql::get_object_sprite_ids() {
	
	std::vector<std::string>sprite_values;
	std::string temp_query_string;
	std::ostringstream ostring_query;
	
	ostring_query << "SELECT id FROM sprites WHERE path LIKE '../../bin/tiles%' OR path LIKE '../../bin/objects%';";
	temp_query_string = ostring_query.str();
	
	return execute_query_with_return(temp_query_string.c_str());

	//Following code returns all ids of the sprite class, including npc's.

	//std::vector<std::string>total = get_data("sprites", "id");
	//return total;
}
std::vector<std::string> sql::get_object_sprite_value(std::string object_id) {
	/*
	This function searches all sprite variables in the database

	return:
	--------
	list of lists of sprite variables: std::vector<std::vector<std::string>>

	returning npc variables order:
	------------------------
	0) id
	1) path
	2) name
	3) size_x
	4) size_y

	*/
	std::vector<std::string>temp_sprite_values;
	std::vector<std::string>sprite_values;
	std::string temp_query_string;
	std::ostringstream ostring_query;
	
	ostring_query
		<< "SELECT " << "path"
		<< " FROM " << "sprites"
		<< " WHERE " << "id" << " == " << object_id << ";"

		<< "SELECT " << "name"
		<< " FROM " << "sprites"
		<< " WHERE " << "id" << " == " << object_id << ";"

		<< "SELECT " << "size_x"
		<< " FROM " << "sprites"
		<< " WHERE " << "id" << " == " << object_id << ";"

		<< "SELECT " << "size_y"
		<< " FROM " << "sprites"
		<< " WHERE " << "id" << " == " << object_id << ";";


	temp_query_string = ostring_query.str();
	temp_sprite_values = execute_query_with_return(temp_query_string.c_str());
	for (auto indexer : temp_sprite_values) {
		sprite_values.push_back(indexer);
	}

	return sprite_values;
}