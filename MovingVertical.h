#pragma once

#include "MovingObj.h"

class MovingVertical : public MovingObj
{
protected:
	float VerticalSpeed;

public:
	MovingVertical();
	MovingVertical(std::shared_ptr<sf::Texture> tex, sf::RenderWindow* window);

	void setSpeed(float speed);

	void update();
	void render(sf::RenderTarget* target);
};

