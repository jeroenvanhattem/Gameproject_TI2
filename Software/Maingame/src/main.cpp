#include <iostream>
#include "sqlite3.h"
#include "sql.hpp"
#include <SFML\Graphics.hpp>
#include "button_actions.hpp"
#include "player.hpp"
#include "music.hpp"
#include "main_menu.hpp"
#include "game.hpp"
#include "leveleditor.hpp"


void intro(sf::Music & m, std::string path) {
	if (!m.openFromFile("../../bin/music/boot.ogg")) {
		std::cout << "Error: Music not found or corrupted file.\n";
	}
	m.play();
}

void intro_stop(sf::Music & m) {
	m.stop();
}

int main( int argc, char* argv[]) {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music m;

	sql database;
	
	music audio(database, buffer, sound);
	music git_gud_audio(database, buffer, sound);
	sf::RenderWindow window{ sf::VideoMode{ 1024, 512 }, "SFML window" };
	
	main_menu menu(window);
	
	
	intro(m, "../../bin/music/boot.ogg");
	menu.gid_gud_splash();
	window.display();

	window.clear();
	menu.loading();
	window.display();
	if (!database.get_level_ids().empty()) {
		audio.play_music_from_map(database.get_level_ids().at(0));
	}
	intro_stop(m);
	leveleditor editor({ 2048, 2048 }, { 32, 32 }, window, database);
	game game(window, database, { 2048, 2048 });
	
	while (window.isOpen()) {

		window.clear();

		menu.show_menu();
		if (menu.button_pressed(menu.level_editor_button, menu.view1)) {
			menu.load_screen();
			editor.editor_loop();
		}
		if (menu.button_pressed(menu.play_game_button, menu.view1)) {
			menu.load_screen();
			game.game_loop();
		}


		window.display();

		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			sf::sleep(sf::milliseconds(1));
		}
	}
}
