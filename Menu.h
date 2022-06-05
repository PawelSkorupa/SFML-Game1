#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Button.h"
#include "Game.h"

class Menu
{
private:

	sf::RenderWindow* window;

	std::unique_ptr<sf::Font> font;
	sf::Text title;
	sf::Text highscoresText;

	bool displayHighscores = false;

	std::vector<Button*> buttons;
	

	Game* game;

	void initWindow();
	void initTexts();
	void initButtons();

public:
	Menu();
	~Menu();

	void run();

	void updatePollEvents();
	void updateHighscores();

	void update();
	void render();
};

