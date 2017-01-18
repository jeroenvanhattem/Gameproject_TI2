#include "rectangle.hpp"


rectangle::rectangle(sf::Vector2f position, sf::Color color, sf::Vector2f end_position) :
	position(position),
	size(end_position - position),
	color(color)
{
	square.setSize(size);
	square.setFillColor(color);
	square.setPosition(position);
}

void rectangle::draw(sf::RenderWindow & window) const {
	window.draw(square);
}

void rectangle::move(sf::Vector2f delta) {
	if (selected) {
		position += delta;
		square.setPosition(position);
	}
}

sf::FloatRect rectangle::get_bounds() {
	return square.getGlobalBounds();
}


std::string rectangle::to_string() {
	std::ostringstream s;
	s << "(" 
		<< position.x
		<< "," 
		<< position.y
		<< ") RECTANGLE "
		<< " ("
		<< position.x + size.x
		<< "," 
		<< position.y + size.y
		<< ")";
	return s.str();
}


void rectangle::is_selected() {
	selected = true;
}
bool rectangle::check_selected() {
	return selected;
}
void rectangle::cancel_selected() {
	selected = false;
}