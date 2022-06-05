#include "Menu.h"

void Menu::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Need for SMiW", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Menu::initTexts()
{
	this->title.setCharacterSize(72);
	this->title.setFillColor(sf::Color::Red);
	this->title.setString("Need for Smiw");
	this->title.setPosition(this->window->getSize().x / 2.f - this->title.getGlobalBounds().width / 2.f, 10.f);

	this->highscoresText.setCharacterSize(48);
	this->highscoresText.setFillColor(sf::Color::White);
	this->highscoresText.setString("empty");
	this->highscoresText.setPosition(this->window->getSize().x / 2.f - this->highscoresText.getGlobalBounds().width / 2.f,
									 this->title.getGlobalBounds().top + this->title.getGlobalBounds().height + 10.f);
}

void Menu::initButtons()
{
	std::string button1txt = "START GAME";
	this->buttons.push_back(new Button(this->window, button1txt, 200.f));

	std::string button2txt = "HIGHSCORES";
	this->buttons.push_back(new Button(this->window, button2txt, 450.f));

	std::string button3txt = "EXIT";
	this->buttons.push_back(new Button(this->window, button3txt, 700.f));

	std::string button4txt = "BACK";
	this->buttons.push_back(new Button(this->window, button4txt, 900.f));
}

Menu::Menu()
{
	this->font = std::unique_ptr<sf::Font>(new sf::Font);
	this->font->loadFromFile("Fonts/cour.ttf");

	this->title.setFont(*(this->font));
	this->highscoresText.setFont(*(this->font));
	this->initWindow();

	//this->game = new Game(this->window);

	this->initTexts();
	this->initButtons();
}

Menu::~Menu()
{
	delete this->window;
	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
		this->buttons.erase(this->buttons.begin() + i);
	}
}

void Menu::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Menu::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		if (this->buttons[0]->getGlobalBounds().contains(mousePos.x, mousePos.y) && !this->displayHighscores)
		{
			this->game = new Game(this->window);
			this->game->run();
			delete this->game;
		}
		if (this->buttons[1]->getGlobalBounds().contains(mousePos.x, mousePos.y) && !this->displayHighscores)
		{
			this->displayHighscores = true;
		}
		if (this->buttons[2]->getGlobalBounds().contains(mousePos.x, mousePos.y) && !this->displayHighscores)
		{
			this->window->close();
		}
		if (this->buttons[3]->getGlobalBounds().contains(mousePos.x, mousePos.y) && this->displayHighscores)
		{
			this->displayHighscores = false;
		}
	}

}

void Menu::updateHighscores()
{
	std::vector<std::string> highscores;

	std::ifstream ifs("highscores.txt");
	std::string line;

	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			highscores.push_back(line);
			highscores.push_back("\n");
		}
	}

	std::string highscoresMerged = "";
	for (std::string score : highscores)
	{
		highscoresMerged += score;
	}

	this->highscoresText.setString(highscoresMerged);
	this->highscoresText.setPosition(this->window->getSize().x / 2.f - this->highscoresText.getGlobalBounds().width / 2.f,
		this->title.getGlobalBounds().top + this->title.getGlobalBounds().height + 10.f);

}

void Menu::update()
{
	this->updatePollEvents();
	this->updateHighscores();
}

void Menu::render()
{
	this->window->clear();

	this->window->draw(this->title);
	
	if (!this->displayHighscores)
	{
		for (size_t i = 0; i < 3; i++)
			this->buttons[i]->render(this->window);
	}
	else
	{
		this->window->draw(this->highscoresText);
		this->buttons[3]->render(this->window);
	}

	this->window->display();
}
