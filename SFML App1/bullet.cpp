#include "bullet.h"

Bullet::Bullet(sf::Vector2f startPos) {
	sprite.setRadius(3.0f);
	sprite.setFillColor(sf::Color::Yellow);
	sprite.setOutlineColor(sf::Color::Red);
	sprite.setPosition(startPos.x, startPos.y - 5.f);
	velocity = sf::Vector2f(10.0f, 0.0f);
	cooldown.setCooldown(sf::seconds(0.5f));
	sf::Vector2f cSize(sprite.getRadius(), sprite.getRadius());
	used = false;
}

Bullet::Bullet(sf::Vector2f startPos, float speed) {
	sprite.setRadius(3.0f);
	sprite.setFillColor(sf::Color(utils::randomInt(0, 255), utils::randomInt(0, 255), utils::randomInt(0, 255)));
	sprite.setOutlineColor(sf::Color::Magenta);
	sprite.setOutlineThickness(1.5f);
	sprite.setPosition(startPos.x, startPos.y - 5.f);
	velocity = sf::Vector2f(speed, 0.0f);
	cooldown.setCooldown(sf::seconds(utils::randomFloat(0.55, 1.05)));  // Randomowy cooldown
	sf::Vector2f cSize(sprite.getRadius(), sprite.getRadius());

	colid.setSize(cSize);
	colid.setPosition(startPos.x, startPos.y - 5.f);
	colid.setOrigin(cSize / 2.0f);
	used = false;
}

void Bullet::setScale(sf::Vector2f scale) {
	sprite.setScale(scale);
}

void Bullet::setSize(float size) {
	sprite.setRadius(size);
}

void Bullet::setTime(sf::Time time) {
	cooldown.setCooldown(time);
}

void Bullet::setDirection(Character* character) {
	sprite.setPosition(character->getCollider().getPosition());
	if (character->getSprite().getScale().x < 0 && velocity.x > 0)
	{
		velocity.x = -velocity.x;
	}
	else if (velocity.x < 0 && character->getSprite().getScale().x > 0) {
		velocity.x = -velocity.x;
	}
}

void Bullet::restart(sf::Vector2f pos) {
	sprite.setPosition(pos);
	colid.setPosition(pos);
	cooldown.restartCooldown();
}

void Bullet::upgrade(int lvl) {
	if (lvl < 10) {
		sprite.setFillColor(sf::Color::Yellow);
		sprite.setOutlineColor(sf::Color::Red);
		//cooldown.setCooldown(sf::seconds(0.5f));
	}

	else if (lvl < 20) {
		sprite.setFillColor(sf::Color::Red);
		sprite.setOutlineColor(sf::Color::Yellow);
		cooldown.setCooldown(sf::seconds(1.5f));
		if (velocity.x > 0)
			velocity.x = 12.0f;
		else velocity.x = -12.0f;
	}

	else if (lvl < 40) {
		sprite.setFillColor(sf::Color::Magenta);
		sprite.setOutlineColor(sf::Color::Yellow);
		cooldown.setCooldown(sf::seconds(1.0f));
		if (velocity.x > 0)
			velocity.x = 14.0f;
		else velocity.x = -14.0f;
	}

	else {
		sprite.setFillColor(sf::Color::White);
		sprite.setOutlineColor(sf::Color::Magenta);
		cooldown.setCooldown(sf::seconds(0.5f));
		if (velocity.x > 0)
			velocity.x = 16.0f;
		else velocity.x = -16.0f;
	}
}

void Bullet::refresh() {
	sprite.move(velocity);
	colid.setPosition(sprite.getPosition());
}

bool Bullet::hit(Character* character) {
	sf::Vector2f colliderDirection;
	if (character->getCollider().checkCollision(getCollider(), colliderDirection, 1.0f)) {
		colliderDirection.x = 1920.f;
		colliderDirection.y = 1080.f;
		colid.setPosition(colliderDirection);
		sprite.setPosition(colliderDirection);
		return 1;
	}
	return 0;
}

void Bullet::hide() {
	sf::Vector2f colliderDirection;
	colliderDirection.x = 1920.f;
	colliderDirection.y = 1080.f;
	colid.setPosition(colliderDirection);
	sprite.setPosition(colliderDirection);
}

void Bullet::setUse(bool use)
{
	used = use;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(sprite);
}

bool Bullet::isUsed()
{
	return used;
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

void Bullet::setVelocity(sf::Vector2f vel) {
	velocity = vel;
}

Collider Bullet::getCollider() {
	colid.setPosition(sprite.getPosition());
	return Collider(colid);
}