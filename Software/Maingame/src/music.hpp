#pragma once
#include "sql.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

class music {
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
<<<<<<< HEAD
	sf::Music intro;
=======
>>>>>>> level_editor_with_sql
	sql database;
	std::string path;

public:
	music(sql & database, sf::SoundBuffer buffer, sf::Sound sound);
<<<<<<< HEAD
	void set_volume(int i);
	void play_music_from_map(std::string map_id);
	void stop_music();
=======
	void play_music_from_map(std::string map_id);
>>>>>>> level_editor_with_sql

};