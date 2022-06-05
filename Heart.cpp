#include "Heart.h"

Heart::Heart(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window, float posX, float scale)
{
	this->sprite.setTexture(*tex);

	this->sprite.setScale(scale, scale);

	this->sprite.setPosition(posX, 40.f);
}

Heart::~Heart()
{
}

void Heart::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
