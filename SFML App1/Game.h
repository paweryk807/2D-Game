#pragma once
#include <time.h>
#include <iostream>
#include "Player.h"
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
	

public:
	Game(sf::View& view, const std::string& playerTexture, const std::string& platform);
	~Game();
	
	bool loadPlatformTexture(const std::string texture);
	bool loadPlayerTexture(const std::string texture);
	bool getActionFromUser();
	void start();
};