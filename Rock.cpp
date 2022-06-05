#include "Rock.h"

//void Rock::initTexture()
//{
//}
//
//void Rock::initSprite()
//{
//}

Rock::Rock(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window, float posX, float scale) : Obstacles(tex, window, posX, scale)
{
	//this->VerticalSpeed = 0.f;

	//this->sprite.setTexture(*tex);

	//this->sprite.setScale(scale, scale);

	//this->sprite.setPosition(posX, 0.f - this->sprite.getGlobalBounds().height);
}

Rock::~Rock()
{
}

void Rock::collisionInteraction(Player* player)
{
	player->looseHp();
}
