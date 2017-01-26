#include "objects.h"

figure::figure(sf::Vector2f position) :
	position{ position }
{}

picture::picture(std::string picture_path, sf::Vector2f position) :
	picture_path(picture_path),
	figure(position)
{
	if (!texture.loadFromFile(picture_path)) {
		std::cout << "Error while loading file.\n";
	}
	sprite.setPosition(location);
	texture.setSmooth(true);
	sprite.setTexture(texture);
}

circle::circle(sf::Vector2f position, float size, sf::Color color) :
	figure(position)
{
	size_in = size;
	set_color = color;
	circ.setRadius(size_in);
	circ.setFillColor(set_color);
	circ.setPosition(position);
}

rectangle::rectangle(sf::Vector2f position, sf::Vector2f size, float outline_thickness, sf::Color color, sf::Color outline_color) :
	figure(position)
{
	size_in = size;
	set_color = color;
	rect.setSize(size_in);
	rect.setFillColor(set_color);
	rect.setPosition(position);
	rect.setOutlineColor(outline_color);
	rect.setOutlineThickness(outline_thickness);
}

void figure::move(sf::Vector2f delta) {
	position += delta;
}

sf::FloatRect circle::getBounds() {
	return circ.getGlobalBounds();
}

sf::FloatRect rectangle::getBounds() {
	return rect.getGlobalBounds();
}

sf::FloatRect picture::getBounds() {
	return sprite.getGlobalBounds();
}

void circle::draw(sf::RenderWindow & window) {
	circ.setPosition(position);
	window.draw(circ);
}

void rectangle::draw(sf::RenderWindow & window) {
	rect.setPosition(position);
	window.draw(rect);
}

void picture::draw(sf::RenderWindow & window) {
	sprite.setPosition(position);
	window.draw(sprite);
}

void figure::jump(sf::Vector2f target) {
	position = target;
}

void figure::jump(sf::Vector2i target) {
	jump(sf::Vector2f(
		static_cast< float >(target.x),
		static_cast< float >(target.y)
	));
}
