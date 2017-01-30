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




int main( int argc, char* argv[]) {
	//sf::SoundBuffer buffer;
	//sf::Sound sound;

	sql database;
	
	//music audio(database, buffer, sound);
	
	sf::RenderWindow window{ sf::VideoMode{ 1920, 1080 }, "SFML window" };
	leveleditor editor({ 1024, 1024 }, { 32, 32 }, window, database);
	main_menu menu(window);
	game game(window, database, { 1024, 1024 });


	//audio.play_music_from_map("1");

	window.display();


	while (window.isOpen()) {

		window.clear();
		game.game_loop();



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
			//	if (event.type == sf::Event::GainedFocus) {
			//	}
			sf::sleep(sf::milliseconds(10));
		}
	}
}
