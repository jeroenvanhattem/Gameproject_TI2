#include <iostream>
#include "sqlite3.h"
#include "sql.hpp"
#include <SFML\Graphics.hpp>
#include "npc.hpp"
#include "button_actions.hpp"
#include "leveleditor.hpp"
#include "main_menu.hpp"
#include "game.hpp"

// https://dcravey.wordpress.com/2011/03/21/using-sqlite-in-a-visual-c-application/
// https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
// http://www.w3schools.com/sql
// If you get a lot of '1's when executing a query, you might miss some parameters

int main( int argc, char* argv[]) {
	sql database;

	sf::RenderWindow window{ sf::VideoMode{ 1920, 1080 }, "SFML window" };
	leveleditor editor({ 1024, 1024 }, { 32, 32 }, window, database);
	main_menu menu(window);
	game game(window, database, { 1024, 1024 });

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
		//	if (event.type == sf::Event::GainedFocus) {
		//	}
			sf::sleep(sf::milliseconds(10));
		}
	}
}
