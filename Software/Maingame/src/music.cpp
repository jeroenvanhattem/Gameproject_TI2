#include "music.hpp"

music::music(sql & database, sf::SoundBuffer buffer, sf::Sound sound) : database(database), buffer(buffer), sound(sound) {}

void music::play_music_from_map(std::string map_id) {
	
	std::string path_to_file;

	std::vector<std::string> music_vector;
	music_vector = database.get_music(map_id);
	path_to_file = music_vector.at(0);

	if (!buffer.loadFromFile(path_to_file)) {
		std::vector<sf::Int16> samples;
		buffer.loadFromSamples(&samples[0], samples.size(), 2, 44100);
	}

	sound.setBuffer(buffer);
	sound.play();
}