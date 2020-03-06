#pragma once
#include <time.h>
#include <iostream>
#include "Player.h"
#include "Functions.h"
#include "Platform.h"

class Game
{
	sf::RenderWindow window;
	sf::View view;
	sf::Texture playerTexture;
	sf::Texture platformTexture;

public:
	Game(sf::RenderWindow window, sf::View view, const std::string playerTexture, const std::string platform);
	~Game();
	
	bool loadPlatformTexture(const std::string texture);
	bool loadPlayerTexture(const std::string texture);

	bool getActionFromUser() {

	}

};