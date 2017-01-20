#include "sql.hpp"

sql::sql() {
	connection = sqlite3_open("database.db", &database);


	if (connection) {
		std::cout << "Can't open the given database" << std::endl;
	}

	else {
		std::cout << "Congratulations, you opened the given database!" << std::endl;
	}


	
}

sql::~sql() {
	sqlite3_close(database);
}

int sql::callback(void *NotUsed, int argc, char **argv, char **azColName) {
	for (int i = 0; i < argc; i++) {
		set_returned(argv[i]);
		std::cout << argv[i];
	}
	std::cout << "\n";
	return 0;
}

void sql::get_data(char* table, char* columnname) {
	query << "SELECT " << columnname << " FROM " << table;
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
}