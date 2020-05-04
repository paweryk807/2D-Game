#pragma once
#include <time.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Soldier.h"
#include "Bird.h"
#include "Menu.h"
#include "Functions.h"
#include "Map.h"
#include "bullet.h"
#include "HUD.h"
#include "EnemySpawner.h"
#include "PlasmaDrone.h"

class Game
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Map> level;
	std::unique_ptr<Player> player;
	HUD hud;
	EnemySpawner spawner;
	Menu menu;
	bool started;
	bool pause;

	unsigned int round;
	unsigned int score;

public:
	Game(std::vector<std::string>& enemiesTextures, const std::string& playerTexture);
	bool addBonus(Bird bonusBird);
	void restart();
	void run();
	void generateLevel();
	void gameOver();
	void getActionFromUser();
	void start();

	~Game();
};