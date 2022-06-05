#pragma once

#include <fstream>
#include <ranges>
#include "MovingObj.h"

class Player : public MovingObj
{
private:
	float horizontalSpeed;
	float Speed;
	float SpeedMax;

	//bool canTurn;

	int points;
	int hp;

	float slipCooldown;
	float slipCooldownMax;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	~Player();

	//const sf::FloatRect getGlobalBounds() const;
	const float getSpeed() const;
	const float getSpeedMax() const;
	const float getHp() const;
	const int getPoints() const;

	void setPosition(float x, float y);
	void addPoints(int pts);
	void looseHp();
	void accelerate(float speed);
	void slowDown(float speed);

	void move(float dirX);
	void addCooldown(float val);
	void setCooldown(float val);
	
	void update();
	void render(sf::RenderTarget* target);

};

