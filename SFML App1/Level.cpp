#include "Level.h"

Level::Level(sf::Vector2i size, sf::Texture& platformTexture) {
	if (size.x > 0 && size.y > 0) {
		this->size = size;
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(19000.0f, 40.0f), sf::Vector2f(10.0f, 400.0f)));
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(700.0f, 360.0f)));
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(480.0f, 360.0f)));
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(900.0f, 300.0f)));
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(1000.0f, 200.0f)));
	}
	else throw std::exception("Bledne wymiary");
}

Level::~Level() {}

bool Level::checkCollision(sf::Vector2f direction, Character* character)
{
	bool collision = false;
	for (Platform& platform : platforms) {
		if (platform.getCollider().checkCollision(character->getCollider(), direction, 1.0f)) {
			character->onCollision(direction);
			collision = true;
		}
		else collision = false;
	}
	return collision;
}

bool Level::wall(Character* character) {
	for (Platform& platform : platforms) {
		if (platform.getCollider().checkCollisionX(character->getCollider())) {
			return true;
		}
	}
	return false;
}

bool Level::checkPosition(Character* character)
{
	if (character->getPosition().x > size.x || character->getPosition().x < 0) {
		return false;
	}
	else if (character->getPosition().y > size.x || character->getPosition().y < 0) {
		return false;
	}
	return true;
}

void Level::draw(sf::RenderWindow& window) {

	for (Platform& platform : platforms) {
		platform.draw(window);
	}

}
sf::Vector2i Level::getSize() {
	return size;
}