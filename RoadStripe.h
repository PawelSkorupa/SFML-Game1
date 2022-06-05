#pragma once
#include "MovingVertical.h"
class RoadStripe : public MovingVertical
{
private:
	//void initTexture();
	//void initSprite();
public:
	RoadStripe(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window);
	~RoadStripe();

	//const sf::FloatRect getGlobalBounds() const;

	//void setSpeed(float speed);

	//void update();
	//void render(sf::RenderTarget* target);
};

