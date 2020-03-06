#include "Game.h"

Game::Game(sf::RenderWindow window, sf::View view, const std::string playerTexture, const std::string platformTexture) {
	if (loadPlatformTexture(platformTexture) && loadPlayerTexture(playerTexture)) {

	}
}

bool Game::loadPlatformTexture(const std::string texture)
{
	if (!platformTexture.loadFromFile(texture)) {
		return 0;
    }
	return 1;
}

bool Game::loadPlayerTexture(const std::string texture)
{
	if (!playerTexture.loadFromFile(texture)) {
		return 0;
	}
	return 1;
}
