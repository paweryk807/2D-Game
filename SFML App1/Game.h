#pragma once
#include <time.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Bird.h"
#include "Menu.h"
#include "Functions.h"
#include "Map.h"
#include "HUD.h"
#include "EnemySpawner.h"
#include "PlayerHandler.h"
class Game {
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Map> level;
	PlayerHandler playerHandler;
	Bird bonusBird;
	HUD hud;
	EnemySpawner spawner;
	Menu menu;
	bool started;
	bool pause;

	unsigned int round;
	unsigned int score;

public:
	Game();
	bool addBonus(Bird bonusBird);
	void soldierHandler(bool& killed);
	void droneHandler(bool& killed);
	void birdHandler(bool& shooted);
	void restart();
	void run();
	void generateLevel();
	void gameOver();
	void start();

	~Game();
};