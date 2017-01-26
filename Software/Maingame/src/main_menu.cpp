#include "main_menu.hpp"

main_menu::main_menu(sf::RenderWindow & window) :
	window(window),
	background("../../bin/pictures/main_background.jpg", { 0,0 }, { 0,0 }),
	level_editor_button("../../bin/pictures/level_editor_button.png", {2150,630}, {0,0}),
	play_game_button("../../bin/pictures/play_game_button.png", { 1950,650 }, { 0,0 })
{
	view1.setCenter({1280,800});
	view1.setSize({2560,1600});
	level_editor_button.rotate(270);
	play_game_button.rotate(270);
}

void main_menu::game_loop() {
	window.setView(view1);
	draw_main_menu();
	button_pressed(level_editor_button, view1);
}

void main_menu::draw_main_menu() {
	background.draw(window);
	level_editor_button.draw(window);
	play_game_button.draw(window);
}

bool main_menu::button_pressed(picture & object, sf::View & view) {
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && object.getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window), view));
}