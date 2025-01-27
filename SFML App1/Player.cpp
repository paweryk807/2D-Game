#include "Player.h"

Player::Player(const std::string& temp) : bullets(bullets) {
	sf::IntRect r(64, 32, 32, 32);
	animation.setRect(r);
	animation.setAnimTime(sf::seconds(0.125));
	loadTexture(temp);
	sprite.setTextureRect(r);
	sf::Vector2f size(1.5 * sprite.getSize().x, 1.5 * sprite.getSize().y);
	setSpeed(4.20, sf::seconds(0.15));
	walkSpeed = getSpeed();
	sprintSpeed = getSpeed() * 1.25;
	maxHP = 100;
	setHealth(maxHP);
	setJumpHeight(14.20);
	setCanJump(true);
	setOnAir(false);
	setCanClimb(false);

	shieldShape.setSize(sf::Vector2f(4.f, 32.f));
	shieldShape.setOrigin(shieldShape.getSize().x / 2, shieldShape.getSize().y / 2 + 5);
	shieldShape.setPosition(getPosition().x + (velocity.x / abs(velocity.x)) * 4, getPosition().y);
	shieldShape.setFillColor(sf::Color::Transparent);
	shieldShape.setOutlineColor(sf::Color::Magenta);
	shieldShape.setOutlineThickness(1.5f);

	shieldCollider.setSize(size);
	strength = 50.f;
	prevLevel = 0;
	level = 0;
	exp = 0.0f;

	for (int i = 0; i < 8; i++)
	{
		bullets.push_back(Bullet(sf::Vector2f(2000, 2000)));
		bullets[i].setTime(sf::seconds(4.f));
	}

	shotCooldown.setCooldown(sf::seconds(0.5));
}

void Player::loadTexture(const std::string& path) {
	if (!texture.loadFromFile(path))
		throw(std::exception("Player Texture error"));
	sprite.setTexture(&texture);
}

float Player::getMaxHP() {
	return maxHP;
}
void Player::moveUp() {
	velocity.y = getSpeed();
	animation.changeMove(32, 19 * 32, 22 * 32, 32, sprite);
}

void Player::moveDown() {
	velocity.y = -getSpeed();
	animation.changeMove(32, 19 * 32, 22 * 32, 32, sprite);
}

void Player::moveRight() {
	velocity.x = getSpeed();
	if (!getOnAir()) {
		animation.changeMove(32, 0, 128, 32, sprite);
	}
}

void Player::moveLeft() {
	velocity.x = -getSpeed();
	if (!getOnAir()) {
		animation.changeMove(32, 0, 128, 32, sprite);
	}
}

void Player::jump() {
	if (getCanJump()) {
		velocity.y = -sqrtf(2.0f * 9.81f * getJumpHeight());
		animation.jump(32, 6 * 32, 8 * 32, 32, sprite, velocity);
	}
}

bool Player::shot() {
	int i = 0;
	if (shotCooldown.elapsed())
		for (auto& elem : bullets) {
			if (!elem.isUsed()) {
				std::cout << i << std::endl;
				elem.restart(getPosition());
				elem.setDirection(this);
				elem.setUse(1);
				shotCooldown.restartCooldown();
				return 1;
			};
			i++;
		}
	return 0;
}
void Player::setSpeed(float temp, sf::Time tempAnim) 
{
	Character::setSpeed(temp);
	animation.setAnimTime(tempAnim);
}

void Player::setWalkSpeed(float speed)
{
	walkSpeed = speed;
	sprintSpeed = 1.25 * walkSpeed;
}
void Player::setLevel(int lvl) {
	if (lvl > 0) {
		level = level;
	}
	else {
		level = 0;
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

float Player::getExp() {
	return exp;
}

bool Player::getShieldState() {
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
	return shieldShape;
}

Collider Player::getShieldCollider() {
	if (getSprite().getScale().x > 0) { // direction
		shieldCollider.setPosition(sf::Vector2f(getPosition().x + 32, getPosition().y));
	}
	else shieldCollider.setPosition(sf::Vector2f(getPosition().x - 32, getPosition().y));
	return Collider(shieldCollider);
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
	sprite.setPosition(600, 350);
	setHealth(100.0);
	setJumpHeight(15.20);
	setCanJump(true);
	setOnAir(false);
	setCanClimb(false);
	setSpeed(4.20, sf::seconds(0.15));
	walkSpeed = getSpeed();
	sprintSpeed = getSpeed() * 1.25;
	strength = 50.f;
	prevLevel = 0;
	level = 0;
	exp = 0.0f;
	maxHP = 100;
	shield = false;

	for (auto& elem : bullets) {
		if (elem.getCooldown().elapsed()) {
			elem.restart(sf::Vector2f(2000, 2000));
			elem.setUse(0);
		}
	}
	while (bullets.size() > 8) {
		bullets.pop_back();
	}
}

bool Player::refresh() {
	for (auto& elem : bullets) {
		elem.refresh();
		if (elem.getCooldown().elapsed()) {
			elem.setUse(0);
		}
	}
	if (shield) {
		if (getSprite().getScale().x > 0) { // direction
			shieldShape.setPosition(getPosition().x + 20, getPosition().y);
		}
		else shieldShape.setPosition(getPosition().x - 20, getPosition().y);
		setSpeed(1.75f, sf::seconds(0.75));
		animation.setAnimTime(sf::seconds(0.25));
	}
	else {
		shieldShape.setPosition(2050, 1150);
		setSpeed(getSpeed(), sf::seconds(0.15));
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
		animation.jump(32, 6 * 32, 8 * 32, 32, sprite, velocity);
	}
	velocity.x = 0.0f;
	velocity.y += 0.9810f * 1.0f;
	if (velocity.y > 17.0f) {
		velocity.y = 9.81f;
	}
	return leveled();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	if (shield) {
		sf::RectangleShape tmp = shieldShape;
		target.draw(tmp);
	}
	target.draw(sprite);
	for (auto elem : bullets) {
		if (!elem.getCooldown().elapsed())
			target.draw(elem);
	}
}

void Player::setSpeedToSprint() {
	setSpeed(sprintSpeed, sf::seconds(0.15 * 1.25));
}

void Player::setSpeedToWalk() {
	setSpeed(walkSpeed, sf::seconds(0.15));
}