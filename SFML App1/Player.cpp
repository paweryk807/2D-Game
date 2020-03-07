#include "Player.h"

Player::Player(const sf::Texture& temp) {

	sprite.setSize(sf::Vector2f(32.0f, 32.0f));
	sprite.setOrigin(sprite.getSize() / 2.0f);
	sprite.setTexture(&temp);
	sprite.setPosition(600, 350);

	rect = sf::IntRect(64, 32, 32, 32);
	sprite.setTextureRect(rect);

	animation = Animation(rect, sf::seconds(0.125));
	velocity = sf::Vector2f(0.0f, 0.0f);
	speed = 2.20;
	jumpHeight = 10.20;
	canJump = true;
	onAir = false;
	canClimb = false;
}

Player::~Player() {}

sf::RectangleShape Player::getSprite() const {
	return sprite;
}

void Player::moveUp() {
	velocity.y = -speed;
	animation.oY(32, 19 * 32, 22 * 32, sprite);
}

void Player::jump() {
	if (canJump) {
		velocity.y = -sqrtf(2.0f * 9.81f * jumpHeight);
		animation.jump(32, 6 * 32, 8 * 32, sprite, velocity);
		canJump = false;
	}	
}

void Player::moveDown() {
	velocity.y = speed;
	animation.oY(32, 19 * 32, 22 * 32, sprite);
}

void Player::moveRight() {
	velocity.x = speed;
	if (!onAir) {
		animation.oX(32, 0, 128, sprite);
	}
}

void Player::moveLeft() {
	velocity.x = -speed;
	if (!onAir) {
		animation.oX(32, 0, 128, sprite);
	}
}

void Player::refresh() {
	
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

void Player::onCollision(sf::Vector2f direction) {
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
void Player::setSpeed(float temp, sf::Time tempAnim) //Sprint Speed
{
	speed = temp;
    animation.setAnimTime(tempAnim);
}

Collider Player::getCollider() {
	return Collider(sprite);
}

sf::Vector2f Player::getPosition() const {
	return sprite.getPosition();
}