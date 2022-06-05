#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Background
{
private:
	sf::RectangleShape road;
	sf::RectangleShape leftGrass;
	sf::RectangleShape rightGrass;

public:
	Background(sf::RenderWindow* window);

	const sf::FloatRect getLeftGrassBounds() const;
	const sf::FloatRect getRightGrassBounds() const;

	void render(sf::RenderTarget* target);
};

