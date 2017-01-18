#include <iostream>
#include <SFML\Graphics.hpp>
#include "background.hpp"
#include "level.hpp"
#include <ostream>


int main(void) {
	std::cout << "Starting application\n";

	sf::RenderWindow window{ sf::VideoMode{ 512, 512 }, "SFML window" };
	
	std::vector<level*>level_list;
	std::string current_level = "#start_level";
	std::string start_level = "../../level_data/start_level.txt";
	level_list.push_back(new level(start_level));

	window.display();


	while (window.isOpen()) {

		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		
		for (auto level : level_list) {
			if (level->get_name() == current_level) {
				level->draw(window);
			}
		}
		
		window.display();

		sf::sleep(sf::milliseconds(50));

	}

	std::cout << "Terminating application\n";

	return 0;
}