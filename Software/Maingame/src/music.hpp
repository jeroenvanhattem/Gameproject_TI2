#pragma once
#include "sql.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

class music {
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music intro;
	sql database;
	std::string path;

public:
	music(sql & database, sf::SoundBuffer buffer, sf::Sound sound);
	void set_volume(int i);
	void play_music_from_map(std::string map_id);
	void stop_music();

};