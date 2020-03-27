#include "Platform.h"

Platform::Platform(sf::Vector2f size, sf::Vector2f position) {
	try {
		body.setSize(size);
		body.setOrigin(size / 2.0f);
		body.setPosition(position);
		body.setTexture(texture);

		body.setTextureRect(sf::IntRect(16 * 7, 0, 16 * 3, 16));
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}

Platform::~Platform() {

}
	
void Platform::draw(sf::RenderWindow& window) {
	window.draw(body);
}

Collider Platform::getCollider() {
	return Collider(body);
}