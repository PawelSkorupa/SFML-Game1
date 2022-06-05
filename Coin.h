#pragma once

#include "Obstacles.h"

class Coin : public Obstacles
{
private:
    //void initTexture();
    //void initSprite();

public:
    Coin(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window, float posX, float scale);
    ~Coin();

    void collisionInteraction(Player* player);
};

