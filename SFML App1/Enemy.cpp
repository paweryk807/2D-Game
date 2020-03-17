#include "Enemy.h"

Enemy::Enemy(const sf::Texture& temp) : Character(temp) {
	sprite.setSize(sf::Vector2f(32.0f, 32.0f));
	sprite.setOrigin(sprite.getSize() / 2.0f);
	sprite.setTexture(&temp);
	sprite.setPosition(800, 350);

	rect = sf::IntRect(64, 64, 32, 32);
	sprite.setTextureRect(rect);
	animation = CharacterAnimation(rect, sf::seconds(0.125));
	velocity = sf::Vector2f(0.0f, 0.0f);
	
	setHealth(100.0);
	setSpeed(2.2, sf::seconds(2.2 * 0.125));
	setJumpHeight(10.20);
	setCanJump(true);
	setOnAir(false);
	setCanClimb(false);

	atackSpeed = 0.5f;
	strength = 1.5f;
}

void Enemy::setAtackSpeed(float aSpd) {
	if (aSpd > 0) {
		atackSpeed = aSpd;
	}
	else {
		atackSpeed = 0;
	}
}

void Enemy::setStrength(float str) {
	if (str > 0) {
		strength = str;
	}
	else {
		strength = 0;
	}
}

float Enemy::getStrength() {
	return strength;
}

float Enemy::getAtackSpeed() {
	return atackSpeed;
}

void Enemy::refresh(Player player, bool lvlColision) {
	// ZROBIC SPRAWDZANIE POPRZEDNIEJ POZYCJI  JESLI JEST TAKA SAMA LUB MINIMALNIE WIEKSZA TO ZEBY SKAKAL BO MOZE SIE ZABLOKOWAL PO PROSTU 

	if((abs(player.getPosition().x - getPosition().x) < 120 && (player.getPosition().y < getPosition().y))) {
		jump();
	}
	if (player.getPosition().x > getPosition().x) {
		velocity.x++;
	}
	else if (player.getPosition().x < getPosition().x) {
		velocity.x--;
	}

	
	sprite.move(velocity.x, velocity.y);
	if (velocity.x > 0.0f) {
		animation.rotateSprite(sprite, 'r');
		moveRight();
	}
	if(velocity.x < 0.0f) {
		animation.rotateSprite(sprite, 'l');
		moveLeft();
	}
	if (velocity.y > 0.0f) {
		setOnAir(true);
		animation.jump(32, 6 * 32, 8 * 32, sprite, velocity);
	}
	if(velocity.y  < 0.0f) {
		setOnAir(true);
		animation.jump(32, 6 * 32, 8 * 32, sprite, velocity);
	}
	velocity.x = 0.0f;
	velocity.y += 0.9810f * 1.0f;
	if (velocity.y > 17.0f) {
		velocity.y = 9.81 * 1.6f;
	}
	
}
