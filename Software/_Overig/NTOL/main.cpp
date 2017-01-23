#include <iostream>
#include <SFML/Graphics.hpp>
#include "npc.hpp"
#include "button_actions.hpp"
#include "tile.hpp"


int main(int argc, char *argv[]) {
	std::cout << "Starting application\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };

	/*std::vector<npc*>npc_list;
	for (float i = 0; i < 4; i++) {
		npc_list.push_back(new npc(window, "../../_assets/sprites/player_sprite.png", { i*64,64 }));
	}*/

	npc player(window, "../../_assets/sprites/player_sprite.png", { 64,64 }, true);
	
	tile t({ 0,0 }, "b");



	while (window.isOpen()) {
		
		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		

		window.clear();
		player.set_action(get_action_name_from_button_keys());
		player.move_player(get_move_direction_from_button_keys());
		
		
		player.draw();
		
		window.display();

		
		sf::sleep(sf::milliseconds(10));
		
	}

	std::cout << "Terminating application\n";
	return 0;
}

