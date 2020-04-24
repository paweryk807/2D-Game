#pragma once
#include <time.h>
#include <iostream>
#include <stdexcept>
#include "Soldier.h"
#include "Menu.h"
#include "Functions.h"
#include "Map.h"
#include "bullet.h"
#include "HealthBar.h"
#include "EnemySpawner.h"
#include <sstream>
#define PLATFORM_PATH "images/sheet.png"
#define BACKGROUND_1 "images/bg.jpg"//background.jpg"
//#define SHEET  "images/sheet.png"

class Game
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Map> level;
	Player* player;
	HealthBar healthBar;
	//std::vector<Soldier*> enemiesToSpawn;
	//std::vector<std::string> enemiesTextures;
	//std::vector<Bullet*> bullets;
	sf::View view;
	sf::Texture playerTexture;
	Menu menu;
	bool started;
	bool pause;

	// RUNDY 
	sf::Font font;
	sf::Text object;

public:
	Game(sf::View& view, std::vector<std::string>& enemiesTextures, const std::string& playerTexture);
	void restart();
	void printRound(int number);
	void run();
	void generateLevel();

	std::vector<Soldier*> addEnemies(const int enemiesToSpawn);
	bool loadTexture(const std::string& texture);
	bool loadEnemiesTextures(std::vector<std::string>& textures);
	void getActionFromUser();
	void start();

	~Game();
};