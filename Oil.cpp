#include "Oil.h"

//void Oil::initTexture()
//{
//}
//
//void Oil::initSprite()
//{
//}

Oil::Oil(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window, float posX, float scale) : Obstacles(tex, window, posX, scale)
{
}

Oil::~Oil()
{
}

void Oil::collisionInteraction(Player* player)
{
	player->setCooldown(0.f);
}
