#include "Coin.h"

//void Coin::initTexture()
//{
//}
//
//void Coin::initSprite()
//{
//}

Coin::Coin(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window, float posX, float scale) : Obstacles(tex, window, posX, scale)
{
	//this->VerticalSpeed = 0.f;

	//this->sprite.setTexture(*tex);

	//this->sprite.setScale(scale, scale);

	//this->sprite.setPosition(posX, 0.f - this->sprite.getGlobalBounds().height);
}

Coin::~Coin()
{
}

void Coin::collisionInteraction(Player* player)
{
	player->addPoints(1000);
}
