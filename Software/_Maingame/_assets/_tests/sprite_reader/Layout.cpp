#include "Layout.hpp"



Layout::Layout(sf::RenderWindow & window):
	window(window)
{
	if (!texture.loadFromFile(grass, sf::IntRect(0, 0, spriteSize, spriteSize))) {
		std::cout << "Error while loading file.";
	}
	texture.setSmooth(true);
}

int Layout::get_tile() {
	return 2;
}

void Layout::set_grid_layout() {

	for (float i = 0; i < windowSize.x; i += spriteSize) {
		for (float j = 0; j < windowSize.y; j += spriteSize) {
			sprite.setTexture(texture);
			sprite.setPosition(i, j);
			window.draw(sprite);

		}
	}
}


Layout::~Layout(){
}
