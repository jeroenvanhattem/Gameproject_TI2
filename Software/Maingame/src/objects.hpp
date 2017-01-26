#ifndef _objects_HPP
#define _objects_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class figure {
public:
	figure(sf::Vector2f position);
	sf::Vector2f position;
	bool selected = 0;

	virtual sf::FloatRect getBounds() = 0;
	virtual void draw(sf::RenderWindow & window) = 0;
	virtual void move(sf::Vector2f delta);

	virtual void jump(sf::Vector2f target);
	virtual void jump(sf::Vector2i target);
};

class self_def_object : public figure {
private:
	sf::ConvexShape convex;
	sf::Texture texture;
	int points = 0;
public:
	std::string picture_path;
	self_def_object(std::string picture_path, sf::Vector2f position, int points);
};

class picture : public figure {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	picture(std::string picture_path, sf::Vector2f position, sf::Vector2f tile_size);
	sf::FloatRect getBounds();
	std::string picture_path;
	sf::Vector2f tile_size;

	void draw(sf::RenderWindow & window);
};

class circle : public figure {
private:
	float size_in;
	sf::Color set_color;
	sf::CircleShape circ;
public:
	circle(sf::Vector2f position, float size, sf::Color color);
	sf::FloatRect getBounds();

	void draw(sf::RenderWindow & window);
};

class rectangle : public figure {
private:
	sf::Vector2f size_in;
	sf::Color set_color;
	sf::RectangleShape rect;
public:
	rectangle(sf::Vector2f position, sf::Vector2f size, float outline_thickness, sf::Color color, sf::Color outline_color);
	sf::FloatRect getBounds();

	void draw(sf::RenderWindow & window);
};

#endif
