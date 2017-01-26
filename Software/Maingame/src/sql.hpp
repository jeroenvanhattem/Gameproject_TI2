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
	//std::ostringstream query;
	int rc;
	int connection;
	char* _ERROR_MESSAGE = 0;
	const char* data = "Callback function called";
	
	
	//private functions
	void sql::check_query_request();

public:

	sql();
	~sql();

	std::vector<std::string> get_data(char* table, char* columnname);
	std::vector<std::string> get_data(char* table, char* columnname, char* condition1, char* condition2);
	void change_data(char* table, char* condition1, char* condition2, char* value1, char* value2);
	void add_data(char* table, char* values);
	void execute_query_without_return(const char* to_be_executed);
	std::vector<std::string> execute_query_with_return(const char* to_be_executed);

	static std::vector<std::string> get_result();
	
	static void set_result(char* x) { result.push_back(x); }
	

	//query functions
	std::vector<std::string> get_player_value(int save, std::string variable_name);
	std::vector<std::string> get_player_sprite(int save);

	//npc functions
	std::vector<std::string> get_npc_value(std::string npc_id);
	std::vector<std::string> get_number_of_npcs();

	//object functions
	std::vector<std::string> get_object_sprite_ids();
	std::vector<std::string> get_object_sprite_value(std::string object_id);
	
	
	

	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};