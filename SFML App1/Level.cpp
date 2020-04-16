#include "Level.h"

Level::Level(sf::Vector2f size, const std::string& backgroundTexture) {
	/*int tab[] =  {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//tMap.load(SHEET, sf::Vector2u(272, 128), tab, 16, 16);
	*/
	if (size.x > 0 && size.y > 0) {
		this->size = size;
		try {
			background.setSize(size);	
			loadBackground(backgroundTexture);
			background.setTexture(&(this->backgroundTexture));
			sf::IntRect x(640, 240, 240, 75);//800, 130, 240, 75);
			platforms.push_back(new Platform(TILES, sf::Vector2f(1980.0f, 40.0f), sf::Vector2f(960, 700.0f),x));

		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}
	}
	else throw std::exception("Bledne wymiary");
	
}

Level::~Level() {}

bool Level::addPlatform(sf::Vector2f pos) {
	platforms.push_back(new Platform(SHEET, sf::Vector2f(140.0f, 40.0f), pos));
	/*if (object->getPosition().x <= size.x && object->getPosition().y <= size.y ) {
		platforms.push_back(*object);
		return 1;
	}*/
	return 0;
}

bool Level::checkCollision(sf::Vector2f direction, Character* character)
{
	bool collision = false;
	for (Platform* platform : platforms) {
		if (platform->getCollider().checkCollision(character->getCollider(), direction, 1.0f)) {
			character->onCollision(direction);
			collision = true;
		}
		else collision = false;
	}
	return collision;
}


bool Level::checkBulletCollision(sf::Vector2f direction, Bullet bullet)
{
	for (Platform* platform : platforms) {
		if (platform->getCollider().checkCollision(bullet.getCollider(), direction, 1.0f)) {
			return true;
		}
	}
	return false;
}


bool Level::wall(Character* character) {
	for (Platform* platform : platforms) {
		if (platform->getCollider().checkCollisionX(character->getCollider())) {
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
	else if (character->getPosition().y > size.y || character->getPosition().y < 0) {
		return false;
	}
	return true;
}

void Level::draw(sf::RenderWindow& window) {
	window.draw(background);
	for (Platform* platform : platforms) {
		window.draw(platform->getBody());
	}

}

bool Level::loadBackground(const std::string& texture) {
	if (!backgroundTexture.loadFromFile(texture)) {
		throw std::exception("unable to open texture file");
        return 0;
	}
    return 1;
}

void Level::reset() {
	while (platforms.size() != 1) {
		platforms.pop_back();
	}
}
sf::Vector2f Level::getSize() {
	return size;
}