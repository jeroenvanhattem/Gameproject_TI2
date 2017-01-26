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
	
	char *_ERROR_MESSAGE = 0;
	int rc;
	int connection;
	const char* data = "Callback function called";
	std::string database_path = "../../bin/database.db";
	char* query_result;

	int counter;

	std::ostringstream query;



public:

	sql();
	~sql();

	std::vector<std::string> get_data(char* table, char* columnname);
	std::vector<std::string> get_data(char* table, char* columnname, char* condition1, char* condition2);
	void change_data(char* table, char* condition1, char* condition2, char* value1, char* value2);
	void add_data(char* table, char* values);
	void execute_query(const char* to_be_executed);
	std::vector<std::string> get_data_from_query(const char* to_be_executed);

	int get_counter() { return counter; }
	static std::vector<std::string> get_result() { return result; }
	
	void set_counter(int x) { counter = x; }
	static void set_result(char* x) { result.push_back(x); }
	

	//query functions
	std::vector<std::string> get_player_variable(int save, std::string variable_name);
	std::vector<std::string> get_player_sprite(int save);

	std::vector<std::string> get_npc_variables();
	
	
	
	

	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};