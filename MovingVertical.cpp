#include "MovingVertical.h"

MovingVertical::MovingVertical()
{
}

MovingVertical::MovingVertical(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window) : VerticalSpeed(0.f)
{
	this->sprite.setTexture(*tex);

	this->sprite.setPosition(window->getSize().x / 2.f - this->sprite.getGlobalBounds().width / 2.f,
		0.f - this->sprite.getGlobalBounds().height);
}

void MovingVertical::setSpeed(float speed)
{
	this->VerticalSpeed = speed;
}

void MovingVertical::update()
{
	this->sprite.move(0.f, this->VerticalSpeed);
}

void MovingVertical::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
