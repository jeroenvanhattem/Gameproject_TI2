#pragma once
#include "sqlite3.h"
#include <iostream>
#include <string>
#include <sstream>

class sql {
private:
	sqlite3 *database;

	char *_ERROR_MESSAGE = 0;
	int rc;
	int connection;
	const char* data = "Callback function called";

	int counter;

	std::ostringstream query;

public:
	static char* returned;

	sql();
	~sql();

	void get_data(char* table, char* columnname);

	int get_counter() { return counter; }
	char* get_returned() { return returned; }
	
	void set_counter(int x) { counter = x; }
	static void set_returned(char* x) { returned = x; }

	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};