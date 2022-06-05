#include "Obstacles.h"

//void Obstacles::initTexture()
//{
//}

//void Obstacles::initSprite()
//{
//}

Obstacles::Obstacles()
{
}

Obstacles::Obstacles(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window, float posX, float scale)
{
	this->VerticalSpeed = 0.f;

	this->sprite.setTexture(*tex);

	this->sprite.setScale(scale, scale);

	this->sprite.setPosition(posX, 0.f - this->sprite.getGlobalBounds().height);
}

void Obstacles::collisionInteraction(Player* player)
{

}
