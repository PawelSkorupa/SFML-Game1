#pragma once

#include <vector>
#include <semaphore>
#include <thread>
//#include <memory>
#include <map>
#include <string>
#include <sstream>
#include "Player.h"
#include "Background.h"
#include "RoadStripe.h"
#include "Obstacles.h"
#include "Rock.h"
#include "Oil.h"
#include "Coin.h"
#include "Heart.h"

class Game
{
private:
	sf::RenderWindow* window;

	Background* background;

	Player* player;

	bool is_running;
	bool isPaused;
	bool is_end;

	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::vector<std::unique_ptr<RoadStripe>> roadStripes;

	float spawnTimer;
	float spawnTimerMax;
	std::vector<Obstacles*> obstacles;

	float rockScale;
	float oilScale;
	float coinScale;

	std::unique_ptr<sf::Font> font;
	sf::Text pointText;
	sf::Text hpText;
	sf::Text PauseText;
	sf::Text GameOverText;
	std::vector<Heart*> hearts;
	float heartScale;

	//private functions
	void initWindow();
	void initTextures();
	void initBackground();
	//void initStripes();
	void initGUI();

	void initPlayer();
	void initObstacles();

public:
	Game(sf::RenderWindow* target);
	virtual ~Game();

	void run();

	void updatePollEvents();
	void updateInput();
	void updateCollision();
	void updateStripes();
	void updateObstacles();
	void ObstaclesCollision(Obstacles* o, std::size_t pos);
	void updateGUI();
	void update();

	void renderBackground(sf::RenderTarget* target);
	void renderGUI(sf::RenderTarget* target);
	void render();

};

