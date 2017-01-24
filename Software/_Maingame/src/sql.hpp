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

	char* get_data(char* table, char* columnname);
	char* get_data(char* table, char* columnname, char* condition1, char* condition2);
	void change_data(char* table, char* condition1, char* condition2, char* value1, char* value2);
	void add_data(char* table, char* values);
	void execute_query(char* to_be_executed);

	int get_counter() { return counter; }
	char* get_result() { return result; }
	
	void set_counter(int x) { counter = x; }
	static void set_result(char* x) { result = x; }


	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};