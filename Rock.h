#pragma once

#include "Obstacles.h"

class Rock : public Obstacles
{
private:
    //void initTexture();
    //void initSprite();

public:
    Rock(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window, float posX, float scale);
    ~Rock();

    void collisionInteraction(Player* player);
};

