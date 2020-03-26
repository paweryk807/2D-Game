#include "Player.h"

Player::Player(const sf::Texture &temp) {
	sf::IntRect r(64, 32, 32, 32);
	animation.setRect(r);
	sprite.setTexture(&temp);
	sprite.setTextureRect(r);	
	setHealth(100.0);
	setSpeed(2.2, sf::seconds(2.2 * 0.125));
	setJumpHeight(10.20);
	setCanJump(true);
	setOnAir(false);
	setCanClimb(false);
	
	atackSpeed = 1.5f;
	strength = 1.5f;
	level = 0;
	exp = 0.0f;
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


