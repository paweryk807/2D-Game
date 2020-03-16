#include "Character.h"

Character::Character(const sf::Texture& temp) {

	sprite.setSize(sf::Vector2f(32.0f, 32.0f));
	sprite.setOrigin(sprite.getSize() / 2.0f);
	sprite.setTexture(&temp);
	sprite.setPosition(600, 350);

	rect = sf::IntRect(64, 32, 32, 32);
	sprite.setTextureRect(rect);
	animation = CharacterAnimation(rect, sf::seconds(0.125));
	velocity = sf::Vector2f(0.0f, 0.0f);
	
	health = 100.0;
	speed = 2.20;
	jumpHeight = 10.20;
	canJump = true;
	onAir = false;
	canClimb = false;
}

Character::~Character() {}

bool Character::getCanClimb() {
	return canClimb;
}

float Character::getHealth() {
	return health;
}


bool Character::getCanJump() {
	return canJump;
}

bool Character::getOnAir() {
	return onAir;
}

void Character::setCanClimb(bool climb) {
	canClimb = climb;
}

void Character::setHealth(float hp) {
	if (hp >= 0) {
		health = hp;
	}
	else {
		health = 0;
	}
}

void Character::setCanJump(bool jump) {
	canJump = jump;
}

void Character::setOnAir(bool air) {
	onAir = air;
}

sf::RectangleShape Character::getSprite() const {
	return sprite;
}

void Character::moveUp() {
	velocity.y = -speed;
	animation.oY(32, 19 * 32, 22 * 32, sprite);
}

void Character::jump() {
	if (canJump) {
		velocity.y = -sqrtf(2.0f * 9.81f * jumpHeight);
		animation.jump(32, 6 * 32, 8 * 32, sprite, velocity);
		canJump = false;
	}	
}

void Character::moveDown() {
	velocity.y = speed;
	animation.oY(32, 19 * 32, 22 * 32, sprite);
}

void Character::moveRight() {
	velocity.x = speed;
	if (!onAir) {
		animation.oX(32, 0, 128, sprite);
	}
}

void Character::moveLeft() {
	velocity.x = -speed;
	if (!onAir) {
		animation.oX(32, 0, 128, sprite);
	}
}

void Character::refresh() {
	
	sprite.move(velocity.x, velocity.y);
	if (velocity.x > 0.0f) {
		animation.rotateSprite(sprite, 'r');
	}
	if(velocity.x < 0.0f) {
		animation.rotateSprite(sprite, 'l');
	}
	if (velocity.y > 0.0f) {
		onAir = true;
		animation.jump(32, 6 * 32, 8 * 32, sprite, velocity);
	}
	if(velocity.y  < 0.0f) {
		onAir = true;
		animation.jump(32, 6 * 32, 8 * 32, sprite, velocity);
	}
	velocity.x = 0.0f;
	velocity.y += 0.9810f * 1.0f;
	if (velocity.y > 17.0f) {
		velocity.y = 9.81 * 1.6f;
	}
	
}

void Character::onCollision(sf::Vector2f direction) {
	if (direction.x < 0.0f) {
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) {
		velocity.y = 0.0f;
		onAir = false;
		canJump = true;
	}
	else if (direction.y > 0.0f) {
		velocity.y = 0.0f;
	}
}
void Character::setSpeed(float temp, sf::Time tempAnim) //Sprint Speed
{
	speed = temp;
    animation.setAnimTime(tempAnim);
}

void Character::correctPosition(sf::Vector2i size) {
	int x = getPosition().x;
	int y = getPosition().y;
	if (x < 0) {
		sprite.setPosition(0, y);
	}
	else if (x > size.x) {
		sprite.setPosition(size.x, y);
	}
	if(y < 0) {
		sprite.setPosition(sprite.getPosition().x, 0);
	}
	else if(y > size.y) {
		sprite.setPosition(sprite.getPosition().x, size.y);
	}
}

Collider Character::getCollider() {
	return Collider(sprite);
}

sf::Vector2f Character::getPosition() const {
	return sprite.getPosition();
}