#pragma once
#include "sqlite3.h"
#include <iostream>
#include <string>
#include <sstream>

static char* result;

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

	sql();
	~sql();

	void get_data(char* table, char* columnname, char* condition1, char* condition2);
	void get_data(char* table, char* columnname);

	void add_data(char* table, char* values);

	int get_counter() { return counter; }
	char* get_result() { return result; }
	
	void change_data(char* table, char* condition1, char* condition2, char* value1, char* value2);

	void set_counter(int x) { counter = x; }
	static void set_result(char* x) { result = x; }

	void execute_query(char* to_be_executed);

	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};