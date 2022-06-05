#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Heart
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	Heart(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window, float posX, float scale);
	~Heart();

	void render(sf::RenderTarget* target);
};

