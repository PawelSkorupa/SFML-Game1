
#include "Game.h"

std::counting_semaphore<3> initSemaphore{ 0 };

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Need for SMiW", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["STRIPE"] = std::make_shared<sf::Texture>();
	this->textures["STRIPE"]->loadFromFile("Textures/stripe.png");
	this->textures["COIN"] = std::make_shared<sf::Texture>();
	this->textures["COIN"]->loadFromFile("Textures/coin.png");
	this->textures["OIL"] = std::make_shared<sf::Texture>();
	this->textures["OIL"]->loadFromFile("Textures/oil.png");
	this->textures["ROCK"] = std::make_shared<sf::Texture>();
	this->textures["ROCK"]->loadFromFile("Textures/rock.png");
	this->textures["HEART"] = std::make_shared<sf::Texture>();
	this->textures["HEART"]->loadFromFile("Textures/heart.png");

	initSemaphore.release(3);

}

void Game::initBackground()
{
	this->background = new Background(this->window);
}

//void Game::initStripes()
//{
//}

void Game::initGUI()
{
	this->font = std::unique_ptr<sf::Font>(new sf::Font);
	this->font->loadFromFile("Fonts/cour.ttf");
	this->pointText.setFont(*(this->font));
	this->pointText.setCharacterSize(32);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("POINTS: ");

	this->hpText.setFont(*(this->font));
	this->hpText.setCharacterSize(32);
	this->hpText.setFillColor(sf::Color::White);
	this->hpText.setString("HP: ");
	this->hpText.setPosition(0.f, 50.f);

	this->PauseText.setFont(*(this->font));
	this->PauseText.setCharacterSize(64);
	this->PauseText.setFillColor(sf::Color::Red);
	this->PauseText.setString("PAUSED");
	this->PauseText.setPosition(0.f, 100.f);

	this->GameOverText.setFont(*(this->font));
	this->GameOverText.setCharacterSize(128);
	this->GameOverText.setFillColor(sf::Color::Red);
	this->GameOverText.setString("GAME OVER");
	this->GameOverText.setPosition(this->window->getSize().x / 2.f - this->GameOverText.getGlobalBounds().width / 2.f,
								   this->window->getSize().y / 2.f - this->GameOverText.getGlobalBounds().height / 2.f);

	initSemaphore.acquire();

	this->heartScale = 0.2f;
	this->hearts.push_back(new Heart(this->textures["HEART"], this->window, 100.f, this->heartScale));
	this->hearts.push_back(new Heart(this->textures["HEART"], this->window, 155.f, this->heartScale));
	this->hearts.push_back(new Heart(this->textures["HEART"], this->window, 210.f, this->heartScale));
}

void Game::initPlayer()
{
	initSemaphore.acquire();
	this->player = new Player();
}

void Game::initObstacles()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;

	initSemaphore.acquire();
	this->rockScale = 0.2f;
	this->oilScale = 0.15f;
	this->coinScale = 0.2f;
}

Game::Game(sf::RenderWindow* target)
{

	this->is_running = true;

	this->isPaused = false;

	this->is_end = false;

	//this->initWindow();

	this->window = target;

	//this->initTextures();

	//this->initBackground();

	//this->initGUI();

	//this->initObstacles();

	//this->initPlayer();

	std::thread th1(&Game::initTextures, this);
	std::thread th2(&Game::initBackground, this);
	std::thread th3(&Game::initGUI, this);
	std::thread th4(&Game::initObstacles, this);
	std::thread th5(&Game::initPlayer, this);

	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();

	this->player->setPosition(this->window->getSize().x / 2.f - this->player->getGlobalBounds().width / 2.f,
		this->window->getSize().y - this->player->getGlobalBounds().height - 100);
}

Game::~Game()
{
	//delete this->window;
	delete this->player;
	delete this->background;
	//delete this->font;

	for (size_t i = 0; i < this->roadStripes.size(); i++)
	{
		//delete this->roadStripes[i];
		this->roadStripes.erase(this->roadStripes.begin() + i);
	}

	for (size_t i = 0; i < this->obstacles.size(); i++)
	{
		delete this->obstacles[i];
		this->obstacles.erase(this->obstacles.begin() + i);
	}

	for (size_t i = 0; i < this->hearts.size(); i++)
	{
		delete this->hearts[i];
		this->hearts.erase(this->hearts.begin() + i);
	}
}

void Game::run()
{
	while (this->window->isOpen() && !this->is_end)
	{
		this->updatePollEvents();

		if (!this->isPaused && this->is_running)
		{
			this->update();

		}
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Escape)
			{
				if (this->is_running)
				{
					if (!this->isPaused) this->isPaused = true;
					else this->isPaused = false;
				}
				else this->is_end = true;
			}
		}
	}
	
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->player->getSpeed() > 0)
		this->player->move(-1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->player->getSpeed() > 0)
		this->player->move(1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->player->getSpeed() <= this->player->getSpeedMax())
		this->player->accelerate(0.01f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->player->getSpeed() >= 0)
		this->player->slowDown(0.05f);
}

void Game::updateCollision()
{
	if (this->player->getGlobalBounds().intersects(this->background->getLeftGrassBounds())) //left grass collision
	{
		this->player->setPosition(this->background->getLeftGrassBounds().width,
								  this->player->getGlobalBounds().top);

		this->player->slowDown(0.05f);
	}

	else if (this->player->getGlobalBounds().intersects(this->background->getRightGrassBounds())) //right grass collision
	{
		this->player->setPosition(this->background->getRightGrassBounds().left - this->player->getGlobalBounds().width,
								  this->player->getGlobalBounds().top);

		this->player->slowDown(0.05f);
	}
}

void Game::updateStripes()
{
	if (roadStripes.size() == 0) roadStripes.push_back(std::make_unique<RoadStripe>(this->textures["STRIPE"], this->window));

	for (size_t i = 0; i < this->roadStripes.size(); i++)
	{
		if (this->player->getSpeed() >= 0)
		{
			this->roadStripes[i]->setSpeed(this->player->getSpeed());
			this->roadStripes[i]->update();
		}

		if (roadStripes[roadStripes.size() - 1]->getGlobalBounds().top > roadStripes[roadStripes.size() - 1]->getGlobalBounds().height + 200.f)
		{
			roadStripes.push_back(std::make_unique<RoadStripe>(this->textures["STRIPE"], this->window));
		}

		if (this->roadStripes[i]->getGlobalBounds().top > this->window->getSize().y)
		{
			//delete this->roadStripes[i];
			this->roadStripes.erase(this->roadStripes.begin() + i);
		}
	}
}

void Game::updateObstacles()
{
	this->spawnTimer += 0.1f * this->player->getSpeed();

	if (this->spawnTimer >= this->spawnTimerMax)
	{
		//unsigned obstacle_type = rand() % 3; // 0 = rock, 1 = oil, 2 = coin

		enum class obstacle_type {rock = 0, oil = 1, coin = 2};

		obstacle_type obs_type = static_cast<obstacle_type>(rand() % 3);

		//obstacle_type = 0;

		if (obs_type == obstacle_type::rock)
		{
			float rock_width = this->textures["ROCK"]->getSize().x * this->rockScale;
			int x = rand() % static_cast<int>(this->background->getRightGrassBounds().left - this->background->getLeftGrassBounds().width - rock_width) + static_cast<int>(this->background->getLeftGrassBounds().width);

			this->obstacles.push_back(new Rock(this->textures["ROCK"], this->window, static_cast<float>(x), this->rockScale));
		}
		else if (obs_type == obstacle_type::oil)
		{
			float oil_width = this->textures["OIL"]->getSize().x * this->oilScale;
			int x = rand() % static_cast<int>(this->background->getRightGrassBounds().left - this->background->getLeftGrassBounds().width - oil_width) + static_cast<int>(this->background->getLeftGrassBounds().width);

			this->obstacles.push_back(new Oil(this->textures["OIL"], this->window, static_cast<float>(x), this->oilScale));
		}
		else if (obs_type == obstacle_type::coin)
		{
			float coin_width = this->textures["COIN"]->getSize().x * this->coinScale;
			int x = rand() % static_cast<int>(this->background->getRightGrassBounds().left - this->background->getLeftGrassBounds().width - coin_width) + static_cast<int>(this->background->getLeftGrassBounds().width);

			this->obstacles.push_back(new Coin(this->textures["COIN"], this->window, static_cast<float>(x), this->coinScale));
		}

		this->spawnTimer = 0.f;
	}

	//unsigned counter = 0;
	//for (auto* obstacle : this->obstacles)
	//{
	//	if (this->player->getSpeed() >= 0)
	//	{
	//		obstacle->setSpeed(this->player->getSpeed());
	//		obstacle->update();
	//	}
	//
	//	if (obstacle->getGlobalBounds().top > this->window->getSize().y)
	//	{
	//		delete this->obstacles.at(counter);
	//		this->obstacles.erase(this->obstacles.begin() + counter);
	//	}
	//	else if (this->player->getGlobalBounds().intersects(obstacle->getGlobalBounds()))
	//	{
	//		obstacle->collisionInteraction(this->player);
	//
	//		delete obstacle;
	//		this->obstacles.erase(this->obstacles.begin() + counter);
	//	}
	//	++counter;
	//}

	for (std::size_t i = 0; i < this->obstacles.size(); i++)
	{
		this->ObstaclesCollision(this->obstacles[i], i);
	}
	//for (size_t i = 0; i < threads.size(); i++) threads[i].join();
	//std::vector<std::thread> threads;
	//for (std::size_t i = 0; i < this->obstacles.size(); i++)
	//{
	//	threads.push_back(std::thread(&Game::ObstaclesCollision, this, obstacles[i], i));
	//}
	//for (size_t i = 0; i < threads.size(); i++) threads[i].join();
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "POINTS: " << this->player->getPoints();
	this->pointText.setString(ss.str());

	if (this->player->getHp() < this->hearts.size())
	{
		delete this->hearts[this->hearts.size() - 1];
		this->hearts.erase(this->hearts.end() - 1);
	}
}

void Game::update()
{
	this->updateInput();
	this->player->update();
	if (this->player->getPoints() > 0) this->player->addPoints(-1);
	this->player->addPoints(static_cast<int>(this->player->getSpeed() * 0.3f));
	this->updateGUI();
	if (this->player->getHp() <= 0) this->is_running = false;
	this->updateCollision();
	this->updateObstacles();
	this->updateStripes();

	//std::thread t1(&Game::updateGUI, this);
	//std::thread t2(&Game::updateStripes, this);
	//t1.join();
	//t2.join();
}

void Game::renderBackground(sf::RenderTarget* target)
{
	this->background->render(target);
}

void Game::ObstaclesCollision(Obstacles* o, std::size_t pos)
{
	if (this->player->getSpeed() >= 0)
	{
		o->setSpeed(this->player->getSpeed());
		o->update();
	}

	if (o->getGlobalBounds().top > this->window->getSize().y)
	{
		delete this->obstacles.at(pos);
		this->obstacles.erase(this->obstacles.begin() + pos);
	}
	else if (this->player->getGlobalBounds().intersects(o->getGlobalBounds()))
	{
		o->collisionInteraction(this->player);

		delete this->obstacles.at(pos);
		this->obstacles.erase(this->obstacles.begin() + pos);
	}
	//++counter;
}

void Game::renderGUI(sf::RenderTarget* target)
{
	target->draw(this->pointText);
	target->draw(this->hpText);

	for (size_t i = 0; i < this->hearts.size(); i++)
		this->hearts[i]->render(this->window);

	if (this->isPaused)
		target->draw(this->PauseText);

	if (!this->is_running)
		target->draw(this->GameOverText);
}

void Game::render()
{
	this->window->clear();

	this->renderBackground(this->window);
	this->renderGUI(this->window);

	for (size_t i = 0; i < this->roadStripes.size(); i++)
		this->roadStripes[i]->render(this->window);

	for (size_t i = 0; i < this->obstacles.size(); i++)
		this->obstacles[i]->render(this->window);

	this->player->render(this->window);

	this->window->display();
}
