
#include "Player.h"

void Player::initVariables()
{
	this->horizontalSpeed = 0.f;
	this->Speed = 0.f;
	this->SpeedMax = 10.f;
	this->points = 0;
	this->hp = 3;
	//this->canTurn = true;
	this->slipCooldownMax = 200.f;
	this->slipCooldown = this->slipCooldownMax;
}

void Player::initTexture()
{
	this->texture.loadFromFile("Textures/car3.png");
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);

	this->sprite.scale(10.f, 10.f);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

std::string cutString(std::string s)
{
	std::size_t pos = s.find('<');
	std::string result = s.substr(pos + 1);
	result = result.substr(0, result.length() - 1);
	return result;
}

Player::~Player()
{
	std::vector<std::string> highscores_str;

	std::ifstream ifs("highscores.txt");
	std::string line;

	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			highscores_str.push_back(line);
		}
	}

	auto highscores_view = highscores_str | std::views::transform(cutString) | std::views::transform([](std::string i) {return std::stoi(i); });

	std::vector<int> highscores;
	std::size_t highscore_size = 0;
	for (auto it = highscores_view.begin(); it != highscores_view.end(); it++)
	{
		highscores.push_back(*it);
		highscore_size++;
	}

	highscores.push_back(this->points);
	highscore_size++;

	std::ranges::sort(highscores, std::ranges::greater());

	std::ofstream ofs;
	ofs.open("highscores.txt");

	if (ofs.is_open())
	{
		for (std::size_t i = 0; i < highscore_size && i < 10; i++)
		{
			ofs << "#" << i + 1 << " <" << highscores[i] << ">\n";
		}
		ofs.close();
	}

}

//const sf::FloatRect Player::getGlobalBounds() const
//{
//	return this->sprite.getGlobalBounds();
//}

const float Player::getSpeed() const
{
	return this->Speed;
}

const float Player::getSpeedMax() const
{
	return this->SpeedMax;
}

const float Player::getHp() const
{
	return this->hp;
}

const int Player::getPoints() const
{
	return this->points;
}

void Player::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Player::addPoints(int pts)
{
	if (this->points >=0)
		this->points += pts;
}

void Player::looseHp()
{
	if (this->hp > 0) this->hp -= 1;
}

void Player::accelerate(float speed)
{
	this->Speed += speed;
}

void Player::slowDown(float speed)
{
	this->Speed -= speed;
}

void Player::move(float dirX)
{
	if (this->slipCooldown >= slipCooldownMax)
		this->sprite.move(this->horizontalSpeed * dirX, 0.f);
}

void Player::addCooldown(float val)
{
	this->slipCooldown += val;
}

void Player::setCooldown(float val)
{
	this->slipCooldown = val;
}

void Player::update()
{
	this->horizontalSpeed = this->Speed * 0.3f;
	if (this->slipCooldown <= this->slipCooldownMax)
		this->addCooldown(1.f);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
