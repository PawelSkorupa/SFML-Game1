#pragma once

#include "Obstacles.h"

class Oil : public Obstacles
{
private:
    //void initTexture();
    //void initSprite();

public:
    Oil(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window, float posX, float scale);
    ~Oil();

    void collisionInteraction(Player* player);
};

