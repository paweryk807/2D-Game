#pragma once
#include <time.h>
#include <iostream>
#include <stdexcept>
#include "Player.h"
#include "Menu.h"
#include "Functions.h"
#include "Level.h"


class Game
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Level> level;
	Player player;
	sf::View view;
	sf::Texture playerTexture;
	sf::Texture platformTexture;
	Menu menu;
	bool started;
	bool pause;
	

public:
	Game(sf::View& view, const std::string& playerTexture, const std::string& platform);
	void restart();
	void run();
	bool showMenu();
	bool hideMenu();

	
	bool loadPlatformTexture(const std::string texture);
	bool loadPlayerTexture(const std::string texture);
	void getActionFromUser();
	void start();

	~Game();
};