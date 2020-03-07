#include "Level.h"

Level::Level(sf::Texture& platformTexture){
	platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(600.0f, 400.0f)));
	platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(700.0f, 360.0f)));
	platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(480.0f, 360.0f)));
	platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(900.0f, 300.0f)));
	platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(1000.0f, 200.0f)));
}

Level::~Level() {}

bool Level::checkCollision(sf::Vector2f direction, Player& player)
{
	bool collision = false;
	for (Platform& platform : platforms) {
		if (platform.getCollider().checkCollision(player.getCollider(), direction, 1.0f)) {
			player.onCollision(direction);
			collision = true;
		}
		else collision = false;
	}
	return collision;
}

void Level::draw(sf::RenderWindow& window) {

	for (Platform& platform : platforms) {
		platform.draw(window);
	}

}