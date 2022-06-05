#include "RoadStripe.h"

//void RoadStripe::initTexture()
//{
//}
//
//void RoadStripe::initSprite()
//{
//}

RoadStripe::RoadStripe(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window) : MovingVertical(tex, window)
{
	//this->sprite.setTexture(*tex);

	//this->sprite.setPosition(window->getSize().x / 2.f - this->sprite.getGlobalBounds().width / 2.f,
	//						 0.f - this->sprite.getGlobalBounds().height);
}

RoadStripe::~RoadStripe()
{

}

