#include "Player.h"

Player::Player(const sf::Texture &temp) : shield(false) {
	sf::IntRect r(64, 32, 32, 32);
	animation.setRect(r);
	animation.setAnimTime(sf::seconds(0.125));
	sprite.setTexture(&temp);
	sprite.setTextureRect(r);	
	sf::Vector2f size(1.5 * sprite.getSize().x, 1.5 * sprite.getSize().y);
	//sprite.setSize(size);
	//sprite.setOrigin(sprite.getOrigin().x, sprite.getOrigin().y + 2.f);
	maxHP = 100;
	setHealth(maxHP);
	setSpeed(1183.9, sf::seconds(1183.9 * 0.125));
	setJumpHeight(14.20);
	setCanJump(true);
	setOnAir(false);
	setCanClimb(false);
	
	shield_shape.setFillColor(sf::Color::Transparent);
	shield_shape.setOutlineColor(sf::Color::Magenta);
	shield_shape.setOutlineThickness(1.5f);
	shield_shape.setSize(sf::Vector2f(4.f, 32.f));
	shield_shape.setOrigin(shield_shape.getSize().x/2, shield_shape.getSize().y / 2 + 5);
	shield_shape.setPosition(getPosition().x + (velocity.x / abs(velocity.x)) * 4, getPosition().y);

	atackSpeed = 2.5f;
	strength = 50.f;
	prevLevel = 0;
	level = 0;
	exp = 0.0f;

}

float Player::getMaxHP() {
	return maxHP;
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

bool Player::getShieldState(){
	return shield;
}

void Player::setShieldState(bool state) {
	shield = state;
}

int Player::getLevel() {
	return level;
}

void Player::addExp(float nExp) {
	exp += nExp;
}

sf::RectangleShape Player::getShield() {
	return shield_shape;
}

Collider Player::getShieldCollider() {
	sf::RectangleShape collid;
	sf::Vector2f xsize(getSprite().getSize().x, shield_shape.getSize().y);
	collid.setSize(xsize);
	collid.setOrigin(shield_shape.getOrigin());
	collid.setPosition(shield_shape.getPosition());
	return Collider(collid);
}
bool Player::leveled() {

	if (level < 10) {
		if (exp > 100) {
			level += 1;
			exp -= 100;
			strength *= 1.1;
			setHealth(maxHP);
			return true;
			// maxHP = 100;
		}
	}
	else if (level < 20) {
		if (exp > 1000) {
			level += 1;
			exp -= 1000;
			strength *= 1.2f;
			maxHP *= 1.1f;
			setHealth(maxHP);
			return true;
		}
	}
	else {
		if (exp > 7000) {
			level += 1;
			exp -= 7000;
			strength *= 1.05f;
			maxHP *= 1.15f;
			setHealth(maxHP);
			return true;
		}
	}
	return false;
}

void Player::reset() {
	Character::reset();
	atackSpeed = 2.5f;
	strength = 50.f;
	prevLevel = 0;
	level = 0;
	exp = 0.0f;
	maxHP = 100;
	shield = false;
}

bool Player::refresh() {

	if (getSprite().getScale().x > 0) { // direction 
		shield_shape.setPosition(getPosition().x + 20, getPosition().y);
	}
	else shield_shape.setPosition(getPosition().x - 20, getPosition().y);

	if (shield) {
		setSpeed(1.75f, sf::seconds(2.f));
	}
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
	return leveled();
}

