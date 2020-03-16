#include "Player.h"

Player::Player(const sf::Texture& temp) : Character(temp) {}

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


