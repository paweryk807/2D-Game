#pragma once
#include <time.h>
#include <iostream>
#include <stdexcept>
#include "Enemy.h"
#include "Menu.h"
#include "Functions.h"
#include "Level.h"
#include "bullet.h"

#define PLATFORM_PATH "images/sheet.png"
#define BACKGROUND_1 "images/background.jpg"
#define SHEET  "images/sheet.png"

class Game
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Level> level;
	Player* player;
	std::vector<Enemy*> enemiesToSpawn;
	std::vector<sf::Texture> enemiesTextures;
	std::vector<Bullet> bullets;
	sf::View view;
	sf::Texture playerTexture;
	Menu menu;
	bool shot;
	bool started;
	bool pause;
	

public:
	Game(sf::View& view, std::vector<std::string>& enemiesTextures, const std::string& playerTexture);
	void restart();
	void printRound(int number);
	void run();
	void generateLevel();

	std::vector<Enemy*> addEnemies(const int enemiesToSpawn, const int type);
	bool loadTexture(const std::string& texture);
	//bool loadPlatformTexture(const std::string texture);
	bool loadEnemiesTextures(std::vector<std::string>& textures, const int type);
	void getActionFromUser();
	void start();

	~Game();
};