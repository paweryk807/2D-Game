#include "Platform.h"

Platform::Platform(const std::string& texture, sf::Vector2f size, sf::Vector2f position) {
	try {
		loadTexture(texture);
		body.setSize(size);
		body.setOrigin(size / 2.0f);
		body.setPosition(position);
		body.setTexture(&(this->texture));
		body.setTextureRect(sf::IntRect(16 * 7, 0, 16 * 3, 16));
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}
	
void Platform::setPosition(sf::Vector2f pos) {
	body.setPosition(pos);
}

sf::Vector2f Platform::getPosition() {
	return body.getPosition();
}

void Platform::draw(sf::RenderWindow& window) {
	window.draw(body);
}

Collider Platform::getCollider() {
	return Collider(body);
}

bool Platform::loadTexture(const std::string& tFile)
{
	if (!texture.loadFromFile(tFile)) {
		throw std::exception("unable to open texture file");
        return 0;
    }
	return 1;
}

Platform::~Platform() {

}