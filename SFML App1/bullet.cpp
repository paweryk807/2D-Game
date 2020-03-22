#include "bullet.h"

Bullet::Bullet(sf::Vector2f startPos) {
	try {
		//loadTexture(TEXTURE_PATH);
		sprite.setRadius(3.0f);
		sprite.setFillColor(sf::Color::Blue);
		//sprite.setTexture(&texture);
		sprite.setPosition(startPos.x, startPos.y - 5.f);
		velocity = sf::Vector2f(2.0f, 0.0f);
		cooldown = Cooldown(sf::seconds(4.f));
		sf::Vector2f cSize(sprite.getRadius() * 0.7f, sprite.getRadius() * 0.7f);
		colid.setSize(cSize);
		
	}
	catch (std::exception e) {
		std::cerr << e.what();
	}


	//rect = sf::IntRect(32, 32, 32, 32);
	//sprite.setTextureRect(rect);
}

void Bullet::setScale(sf::Vector2f scale) {
	sprite.setScale(scale);
}

bool Bullet::loadTexture(const std::string path) {
	if (!texture.loadFromFile(path)) {
		throw std::exception("cannot open bullet texture");
	}
}
void Bullet::restart() {
	cooldown.restartCooldown();
}

void Bullet::setDirection(Character* character) {
	sprite.setPosition(character->getCollider().getPosition());
	if (character->getVelocity().x < 0);
	{
		velocity.x = -velocity.x;
	}
}
void Bullet::refresh() {
		sprite.move(velocity);
}

sf::CircleShape Bullet::getSprite() {
	return sprite;
}

sf::Vector2f Bullet::getVelocity() {
	return velocity;
}

Cooldown Bullet::getCooldown() {
	return cooldown;
}

void Bullet::setIntRect(sf::IntRect rect) {
	this->rect = rect;
}

void Bullet::setVelocity(sf::Vector2f vel) {
	velocity = vel;
}

Collider Bullet::getCollider() {
	return Collider(colid);
}


