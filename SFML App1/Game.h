#pragma once
#include <time.h>
#include <iostream>
#include <stdexcept>
#include "Soldier.h"
#include "Menu.h"
#include "Functions.h"
#include "Level.h"
#include "bullet.h"

#define PLATFORM_PATH "images/sheet.png"
#define BACKGROUND_1 "images/bg.jpg"//background.jpg"
#define SHEET  "images/sheet.png"

class Game
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Level> level;
	Player* player;
	std::vector<Soldier*> enemiesToSpawn;
	std::vector<std::string> enemiesTextures;
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

	std::vector<Soldier*> addEnemies(const int enemiesToSpawn, const int type);
	bool loadTexture(const std::string& texture);
	//bool loadPlatformTexture(const std::string texture);
	bool loadEnemiesTextures(std::vector<std::string>& textures);
	void getActionFromUser();
	void start();

	~Game();
};