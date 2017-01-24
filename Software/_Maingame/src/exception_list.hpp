#pragma once

#include <iostream>

class end_of_file : public std::exception {};

class invalid_position : public std::exception {
private:
	std::string s;
public:
	invalid_position(char c):
		s(std::string("invalid position character [") + c + "]")
	{}
	const char * what() const override {
		return s.c_str();
	}

};

class unknown_shape : public std::exception {
private:
	std::string s;
public:
	unknown_shape(const std::string & name):
		s(std::string( "unknown shape [" ) + name + "]")
	{}

	const char * what() const override {
		return s.c_str();
	}

};

class unknown_tile : public std::exception {
private:
	std::string s;
public:
	unknown_tile(const std::string & name) :
		s(std::string("unknown color [") + name + "]")
	{}

	const char * what() const override {
		return s.c_str();
	}

};


