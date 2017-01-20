#include <iostream>
#include "_SQLite/sqlite3.h"
#include "sql.hpp"


// https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm

int main( int argc, char* argv[]) {
	std::cout << "Checking CMD" << std::endl;
	int _ENDING;

	sql database;

	database.get_data("item", "name");

	std::cin >> _ENDING; // This will prefend the program from closing directly after executing.
}
