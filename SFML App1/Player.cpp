#include "Player.h"

Player::Player(const sf::Texture &temp) {
	sf::IntRect r(64, 32, 32, 32);
	animation.setRect(r);
	animation.setAnimTime(sf::seconds(0.125));
	sprite.setTexture(&temp);
	sprite.setTextureRect(r);	
	setHealth(100.0);
	setSpeed(1183.9, sf::seconds(1183.9 * 0.125));
	setJumpHeight(14.20);
	setCanJump(true);
	setOnAir(false);
	setCanClimb(false);
	
	atackSpeed = 2.5f;
	strength = 50.f;
	level = 0;
	exp = 0.0f;
}

void Player::moveUp() {
	velocity.y = getSpeed();
	animation.oY(32, 19 * 32, 22 * 32, sprite);
}

void Player::moveDown() {
	velocity.y = -getSpeed();
	animation.oY(32, 19 * 32, 22 * 32, sprite);
}

void Player::moveRight() {
	velocity.x = getSpeed();
	if (!getOnAir()) {
		animation.oX(32, 0, 128, sprite);
	}
}

void Player::moveLeft() {
	velocity.x = -getSpeed();
	if (!getOnAir()) {
		animation.oX(32, 0, 128, sprite);
	}
}

void Player::jump() {
	if (getCanJump()) {
		velocity.y = -sqrtf(2.0f * 9.81f * getJumpHeight());
		animation.jump(32, 6 * 32, 8 * 32, sprite, velocity);
	}
}

void Player::setSpeed(float temp, sf::Time tempAnim) //Sprint Speed
{
	Character::setSpeed(temp);
	animation.setAnimTime(tempAnim);
}

void Player::setAnimation(CharacterAnimation& a) {
	animation = a;
}
void Player::setLevel(int lvl) {
	if (lvl > 0) {
		level = level;
	}
	else {
		level = 0;
	}
}

void Player::setAtackSpeed(float aSpd) {
	if (aSpd > 0) {
		atackSpeed = aSpd;
	}
	else {
		atackSpeed = 0;
	}
}

void Player::setStrength(float str) {
	if (str > 0) {
		strength = str;
	}
	else {
		strength = 0;
	}
}

float Player::getStrength() {
	return strength;
}

float Player::getAtackSpeed() {
	return atackSpeed;
}

float Player::getExp() {
	return exp;
}

int Player::getLevel() {
	return level;
}

void Player::setExp(float nExp) {
	if (nExp > 0) {
	exp = nExp;
	}
	else {
		exp = 0;
	}
}

void Player::refresh() {
	sprite.move(velocity.x, velocity.y);
	if (velocity.x > 0.0f) {
		animation.rotateSprite(sprite, 'r');
	}
	if (velocity.x < 0.0f) {
		animation.rotateSprite(sprite, 'l');
	}
	if (velocity.y != 0.0f) {
		setOnAir(true);
		setCanJump(false);
		animation.jump(32, 6 * 32, 8 * 32, sprite, velocity);
	}
	velocity.x = 0.0f;
	velocity.y += 0.9810f * 1.0f;
	if (velocity.y > 17.0f) {
		velocity.y = 9.81 * 1.6f;
	}
}

