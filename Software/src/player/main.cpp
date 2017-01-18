#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.hpp"


int main(int argc, char *argv[]) {
	std::cout << "Starting application\n";

	sf::RenderWindow window{ sf::VideoMode{ 512, 512 }, "SFML window" };
	std::string player_sprite = "../../sprites/player_sprite.png";

	
	window.display();
	player ralf(player_sprite);
	player ralf2(player_sprite);
	player ralf3(player_sprite);
	player ralf4(player_sprite);
	sf::Texture texture;

	
	while (window.isOpen()) {

		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		ralf.draw(window);
		ralf.move({0,-2});

		ralf2.draw(window);
		ralf2.move({ 0,2 });

		ralf3.draw(window);
		ralf3.move({ -2,0 });

		ralf4.draw(window);
		ralf4.move({ 2,0 });


		window.display();

		sf::sleep(sf::milliseconds(50));
		
	}

	std::cout << "Terminating application\n";
	return 0;
}

