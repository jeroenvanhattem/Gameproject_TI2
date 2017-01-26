#ifndef _main_menu_HPP
#define _main_menu_HPP

#include "objects.hpp"

class main_menu {
public:
	sf::View view1;
	picture level_editor_button;
	picture play_game_button;

	main_menu(sf::RenderWindow & window);
	void game_loop();
	bool button_pressed(picture & object, sf::View & view);
private:
	sf::RenderWindow & window;
	picture background;

	void draw_main_menu();
};

#endif
