#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class MovingObj
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
private:
	//virtual void initTexture() = 0;
	//virtual void initSprite() = 0;

public:
	const sf::FloatRect getGlobalBounds();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};