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
		set_result(argv[0]);
		std::cout << result;
	}
	std::cout << "\n";
	return 0;
}

void sql::get_data(char* table, char* columnname, char* condition1, char* condition2) {
	query << "SELECT " << columnname << " FROM " << table << " WHERE " << condition1 << " = " << condition2 << ";";
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

void sql::get_data(char* table, char* columnname) {
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
}

void sql::execute_query(char* to_be_executed) {
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