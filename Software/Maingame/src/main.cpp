#include <iostream>
#include "sqlite3.h"
#include "sql.hpp"
#include <SFML\Graphics.hpp>
#include "npc.hpp"
#include "button_actions.hpp"
#include "leveleditor.hpp"


// https://dcravey.wordpress.com/2011/03/21/using-sqlite-in-a-visual-c-application/
// https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
// http://www.w3schools.com/sql
// If you get a lot of '1's when executing a query, you might miss some parameters


int main( int argc, char* argv[]) {
	sql database;

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };

	leveleditor editor({ 1024, 1024 }, { 32, 32 }, window, database );

	


	while (window.isOpen()) {
		window.clear();
		
		editor.editor_loop();


		window.display();


		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}


		sf::sleep(sf::milliseconds(10));
	}
}
