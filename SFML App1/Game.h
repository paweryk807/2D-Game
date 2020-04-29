#pragma once
#include <time.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Soldier.h"
#include "Menu.h"
#include "Functions.h"
#include "Map.h"
#include "bullet.h"
#include "HUD.h"
#include "EnemySpawner.h"

class Game
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Map> level;
	Player* player;
	HUD hud;
	EnemySpawner spawner;
	sf::View view;
	sf::Texture playerTexture;
	Menu menu;
	bool started;
	bool pause;

	unsigned int round;
	unsigned int score;

	// RUNDY 
	sf::Font font;
	sf::Text object;

public:
	Game(sf::View& view, std::vector<std::string>& enemiesTextures, const std::string& playerTexture);
	void restart();
	void printRound(int number);
	void run();
	void generateLevel();

	//std::vector<Soldier*> addEnemies(const int enemiesToSpawn);
	void gameOver();
	bool loadTexture(const std::string& texture);
	//bool loadEnemiesTextures(std::vector<std::string>& textures);
	void getActionFromUser();
	void start();

	~Game();
};