#pragma once
#include <time.h>
#include <iostream>
#include <stdexcept>
#include "Player.h"
#include "Enemy.h"
#include "Menu.h"
#include "Functions.h"
#include "Level.h"


class Game
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Level> level;
	Player player;
	std::vector<Enemy> enemies;
	std::vector<sf::Texture> enemiesTextures;
	sf::View view;
	sf::Texture playerTexture;
	sf::Texture platformTexture;
	Menu menu;
	bool started;
	bool pause;
	

public:
	Game(sf::View& view, std::vector<std::string>& enemiesTextures, const std::string& playerTexture, const std::string& platform);
	void restart();
	void run();

	std::vector<Enemy> addEnemies(const int enemiesToSpawn, const int type);

	bool loadPlatformTexture(const std::string texture);
	bool loadPlayerTexture(const std::string texture);
	bool loadEnemiesTextures(std::vector<std::string>& textures, const int type);
	void getActionFromUser();
	void start();

	~Game();
};