#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Button
{
private:
	sf::RectangleShape shape;
	
	sf::Text text;
	std::unique_ptr<sf::Font> font;

public:
	Button(sf::RenderWindow* window, std::string txt, float posY);
	~Button();

	const sf::FloatRect getGlobalBounds() const;

	void render(sf::RenderTarget* target);
};

