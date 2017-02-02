#ifndef _main_menu_HPP
#define _main_menu_HPP

#include "objects.hpp"

class main_menu {
<<<<<<< HEAD
private:
	sf::RenderWindow & window;
	picture background;

	void draw_main_menu();

=======
>>>>>>> level_editor_with_sql
public:
	sf::View view1;
	sf::View view2;
	picture level_editor_button;
	picture play_game_button;
	picture load_screen_pic;
<<<<<<< HEAD
	picture gid_gud;
=======
>>>>>>> level_editor_with_sql

	main_menu(sf::RenderWindow & window);
	void show_menu();
	bool button_pressed(picture & object, sf::View & view);
	void load_screen();
<<<<<<< HEAD
	void gid_gud_splash();
	void loading();

=======
private:
	sf::RenderWindow & window;
	picture background;

	void draw_main_menu();
>>>>>>> level_editor_with_sql
};

#endif
