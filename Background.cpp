
#include "Background.h"

Background::Background(sf::RenderWindow* window)
{
	this->road = sf::RectangleShape(sf::Vector2f(window->getSize()));
	this->road.setFillColor(sf::Color(128.f, 128.f, 128.f));

	this->leftGrass = sf::RectangleShape(sf::Vector2f(window->getSize().x / 3.f, window->getSize().y));
	this->leftGrass.setFillColor(sf::Color(60.f, 176.f, 67.f));

	this->rightGrass = this->leftGrass;
	this->rightGrass.setPosition(2.f * window->getSize().x / 3.f, 0.f);
}

const sf::FloatRect Background::getLeftGrassBounds() const
{
	return this->leftGrass.getGlobalBounds();
}

const sf::FloatRect Background::getRightGrassBounds() const
{
	return this->rightGrass.getGlobalBounds();
}

void Background::render(sf::RenderTarget* target)
{
	target->draw(this->road);
	target->draw(this->leftGrass);
	target->draw(this->rightGrass);
}
