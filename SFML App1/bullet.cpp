#include "bullet.h"

Bullet::Bullet(sf::Vector2f startPos) {
	try {
		loadTexture(TEXTURE_PATH);
		sprite.setRadius(3.0f);
		sprite.setFillColor(sf::Color::Yellow);
		sprite.setOutlineColor(sf::Color::Red);
		//sprite.setTexture(&texture); 
		sprite.setPosition(startPos.x, startPos.y - 5.f);
		velocity = sf::Vector2f(10.0f, 0.0f);
		animation.setAnimTime(sf::seconds(0.5f));
		sf::Vector2f cSize(sprite.getRadius(), sprite.getRadius());
		colid.setSize(cSize);
		colid.setPosition(startPos.x, startPos.y - 5.f);
		colid.setOrigin(cSize / 2.0f);
		//rect = sf::IntRect(32, 32, 32, 32);  
		//sprite.setTextureRect(rect);
	}
	catch (std::exception e) {
		std::cerr << e.what();
	}
}



void Bullet::setScale(sf::Vector2f scale) {
	sprite.setScale(scale);
}

bool Bullet::loadTexture(const std::string path) {
	if (!texture.loadFromFile(path)) {
		throw std::exception("cannot open bullet texture");
	}
}

void Bullet::setDirection(Character* character) {
	sprite.setPosition(character->getCollider().getPosition());
	if (character->getSprite().getScale().x < 0 && velocity.x > 0)
	{
		velocity.x = -velocity.x;
	}
	else if(velocity.x < 0 && character->getSprite().getScale().x > 0) {
		velocity.x = -velocity.x;
	}
}

void Bullet::restart(sf::Vector2f pos) {
	sprite.setPosition(pos);
	colid.setPosition(pos);
	animation.restartCooldown();
}

void Bullet::refresh() {
		sprite.move(velocity);
		colid.setPosition(sprite.getPosition());
}

bool Bullet::hit(Character* character) {
	sf::Vector2f colliderDirection;   
	if (character->getCollider().checkCollision(getCollider(), colliderDirection , 1.5f)) {
		colliderDirection.x = 1920.f;
		colliderDirection.y = 1080.f;
		colid.setPosition(colliderDirection);
		sprite.setPosition(colliderDirection);
		return 1;
	}
	return 0;
}

sf::CircleShape Bullet::getSprite() {
	return sprite;
}

sf::Vector2f Bullet::getVelocity() {
	return velocity;
}

Cooldown Bullet::getCooldown() {
	return animation.getAnimationCooldown();
}

void Bullet::setIntRect(sf::IntRect rect) {
	animation.setRect(rect);
}

void Bullet::setVelocity(sf::Vector2f vel) {
	velocity = vel;
}

Collider Bullet::getCollider() {
	return Collider(colid);
}

 