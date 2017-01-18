#include <iostream>
#include <SFML/Graphics.hpp>
#include "Layout.hpp"


int main(int argc, char *argv[]) {
	std::cout << "Starting application\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	



	Layout layout(window);
	
	

	while (window.isOpen()) {

		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		layout.set_grid_layout();
		window.display();

		sf::sleep(sf::milliseconds(20));

	}

	std::cout << "Terminating application\n";
	return 0;
}

