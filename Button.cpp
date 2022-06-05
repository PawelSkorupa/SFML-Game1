#include "Button.h"

Button::Button(sf::RenderWindow* window, std::string txt, float posY)
{

	this->shape.setSize(sf::Vector2f(200.f, 100.f));
	this->shape.setPosition(window->getSize().x / 2.f - this->shape.getGlobalBounds().width / 2.f, posY);
	this->shape.setFillColor(sf::Color::Blue);
	this->font = std::unique_ptr<sf::Font>(new sf::Font);
	this->font->loadFromFile("Fonts/cour.ttf");

	this->text.setFont(*(this->font));
	this->text.setCharacterSize(16);
	this->text.setFillColor(sf::Color::White);
	this->text.setString(txt);
	this->text.setPosition(this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2,
						   this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height / 2 - this->text.getGlobalBounds().height);
}

Button::~Button()
{
	//delete this->font;
}

const sf::FloatRect Button::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
