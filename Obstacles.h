#pragma once

#include "MovingVertical.h"
#include "Player.h"

class Obstacles : public MovingVertical
{
private:
	//void initTexture();
	//void initSprite();

public:
	Obstacles();
	Obstacles(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window, float posX, float scale);

	virtual void collisionInteraction(Player* player);
};