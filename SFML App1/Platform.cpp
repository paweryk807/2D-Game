#include "Platform.h"
Platform::Platform(sf::RectangleShape& body) : body(body) {}


void Platform::setPosition(sf::Vector2f pos) {
	body.setPosition(pos);
}

sf::Vector2f Platform::getPosition() {
	return body.getPosition();
}

sf::RectangleShape Platform::getBody() {
	return body;
}
void Platform::setBody(sf::RectangleShape& body) {
	this->body = body;
}


MapCollider Platform::getCollider() {
	return MapCollider(body);
}

Platform::~Platform() {

}