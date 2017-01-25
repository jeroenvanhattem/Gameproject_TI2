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
	/*
	De gegevens zitten hier goed, alleen word het bij het opslaan verkeerd gezet.
	*/

	for (int i = 0; i < argc; i++) {
		set_result(argv[0]);
		for (auto index : get_result()) {
			std::cout << index << "\t";
		}
	}
	std::cout << "\n";
	return 0;
}


std::vector<std::string> sql::get_data(char* table, char* columnname, char* condition1, char* condition2) {
	query << "SELECT " << columnname << " FROM " << table << " WHERE " << condition1 << " == " << condition2 << ";";
	std::string query_string = query.str();
	
	
	rc = sqlite3_exec(database, query_string.c_str(), callback, 0, &_ERROR_MESSAGE);
	
	while (rc = sqlite3_exec(database, query_string.c_str(), callback, 0, &_ERROR_MESSAGE) != 0) {
		std::cout << rc << "\t" << "\n";
	}
	std::cout << rc << "\t" << "\n";

	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE << std::endl;
		sqlite3_free(_ERROR_MESSAGE);
	}
	else {
		std::cout << "Reading succesfull" << std::endl;
	}
	//std::cout << get_result();

	return get_result();
}



std::vector<std::string> sql::get_data(char* table, char* columnname) {
	query << "SELECT " << columnname << " FROM " << table << ";";
	std::string query_string = query.str();


	while (rc = sqlite3_exec(database, query_string.c_str(), callback, 0, &_ERROR_MESSAGE) != 0) {
		std::cout << rc;
	}

	set_counter(0);

	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE << std::endl;
		sqlite3_free(_ERROR_MESSAGE);
	}
	else {
		std::cout << "Reading succesfull" << std::endl;
	}
	//std::cout << get_result();

	return result;
}

void sql::execute_query(const char* to_be_executed) {
	while (rc = sqlite3_exec(database, to_be_executed, callback, 0, &_ERROR_MESSAGE) != 0) {
		std::cout << rc;
	}

	set_counter(0);

	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE << std::endl;
		sqlite3_free(_ERROR_MESSAGE);
	}
	else {
		std::cout << "Executing succesfull" << std::endl;
	}
}

void sql::add_data(char* table, char* values) {
	query << "INSERT INTO " << table << " VALUES( NULL, " << values << ");";
	//query << "INSERT INTO test VALUES('Data', 40);";
	//query << "SELECT * FROM maps;";
	std::string query_string = query.str();


	rc = sqlite3_exec(database, query_string.c_str(), callback, 0, &_ERROR_MESSAGE);
	std::cout << rc;
	
	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE << std::endl;
		sqlite3_free(_ERROR_MESSAGE);
	}
	else {
		std::cout << "Records added succesfull" << std::endl;
	}
}

void sql::change_data(char* table, char* condition1, char* condition2, char* value1, char* value2) {
	query << "UPDATE " << table << " SET " << value1 << " = '" << value2 << "' WHERE " << condition1 << " = " << condition2 << ";";
	std::string query_string = query.str();

	rc = sqlite3_exec(database, query_string.c_str(), callback, 0, &_ERROR_MESSAGE);
	std::cout << rc;

	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE << std::endl;
		sqlite3_free(_ERROR_MESSAGE);
	}
	else {
		std::cout << "Changing data succesfull" << std::endl;
	}

}





std::vector<std::string> sql::get_player_variable(int save, std::string variable_name) {
	query	<< "SELECT " << variable_name
			<< " FROM player "
			<< "WHERE id == " << save << ";";


	std::string query_string = query.str();
	int x = 0;


	while (rc = sqlite3_exec(database, query_string.c_str(), callback, 0, &_ERROR_MESSAGE) != 0) {
		std::cout << rc << "\t" << x << "\n";
		x++;
	}

	set_counter(0);

	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE << std::endl;
		sqlite3_free(_ERROR_MESSAGE);
	}
	else {
		std::cout << "Reading succesfull" << std::endl;
	}
	return get_result();


}


std::vector<std::string> sql::get_player_sprite(int save) {
	query	<< "SELECT sprites.path "
			<< "FROM sprites, player "
			<< "WHERE sprites.id = player.sprite_id "
			<< "AND name = " << save << ";";

	std::string query_string = query.str();
	int x = 0;
	
	while (rc = sqlite3_exec(database, query_string.c_str(), callback, 0, &_ERROR_MESSAGE) != 0) {
		std::cout << rc << "\t" << x << "\n";
		x++;
	}

	set_counter(0);

	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE << std::endl;
		sqlite3_free(_ERROR_MESSAGE);
	}
	else {
		std::cout << "Reading succesfull" << std::endl;
	}
	return get_result();

}

std::vector<std::string> sql::get_data_from_query(const char* to_be_executed) {
	//DIT GAAT MIS
	while (rc = sqlite3_exec(database, to_be_executed, callback, 0, &_ERROR_MESSAGE) != 0) {
		std::cout << rc;
	}

	set_counter(0);

	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE << std::endl;
		sqlite3_free(_ERROR_MESSAGE);
	}
	else {
		std::cout << "Executing of get_data_from_query succesfull" << std::endl;
		//std::cout << "Reading succesfull" << std::endl;
	}
	//std::cout << get_result();

	return result;

}


std::vector<std::string> sql::get_npc_variables() {
	/*
	name
	sprite
	level
	class
	position
	quest

	*/
	std::vector<std::string>npc_id;
	std::vector<std::string>npc_values;
	std::string temp_query;
	
	//char* temp_total_rows = get_data("sqlite_sequence", "seq", "name", "NPC");
	
	//temp_query = ("SELECT COUNT(*) FROM sqlite_sequence;");
	//char* temp_total_rows = get_data_from_query(temp_query.c_str());
	//std::cout << temp_total_rows << "\n"; // <-- HIER GAAT HET MIS!
	//int rows_in_npc = int(temp_total_rows - '0');

	
	//char char_indexer;
	//char* char_pointer_indexer;

	//for (int i = 0; i < rows_in_npc; i++) {
		//char_indexer =  i+'0';
		//char_pointer_indexer = &char_indexer;
		//std::cout << char_pointer_indexer << " | ";

		//temp_query = ("SELECT name FROM npc WHERE npc.id == " + i);
	std::vector<std::string>temp_name = get_data("NPC", "name", "id", "1");
	for (auto indexer : temp_name) {
		npc_values.push_back(indexer);

	}
	
	temp_query = ("SELECT sprites.path FROM sprites, NPC WHERE sprites.id == sprites.id AND NPC.id == 1;");
	std::vector<std::string>temp_sprite_path = get_data_from_query(temp_query.c_str());
	for (auto indexer : temp_sprite_path) {
		npc_values.push_back(indexer);

	}


		////temp_query = ("SELECT level FROM NPC WHERE NPC.id == " + i + ';');
		//npc_values.push_back(get_data("NPC", "name", "id", "1"));

		////temp_query = ("SELECT class_id FROM NPC WHERE factions.id == npc.class_id AND NPC.id == " + i + ';');
		//npc_values.push_back(get_data("NPC", "class_id", "id", "1"));


		////temp_query = ("SELECT position_x FROM NPC WHERE NPC.id == " + i + ';');
		//npc_values.push_back(get_data("NPC", "position_x", "id", "1"));

		////temp_query = ("SELECT position_y FROM NPC WHERE NPC.id == " + i + ';');
		//npc_values.push_back(get_data("NPC", "position_y", "id", "1"));

		////temp_query = ("SELECT quest_id FROM NPC WHERE NPC.id == " + i + ';');
		//npc_values.push_back(get_data("NPC", "quest_id", "id", "1"));
		
		for (auto npc : npc_values) {
			std::cout << npc << "\t";
		}
		std::cout << "\n";

	//}

	return npc_values;
}








