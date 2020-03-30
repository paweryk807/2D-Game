#include "Enemy.h"
Enemy::Enemy(float atackSpeed, float strength) : atackSpeed(atackSpeed), strength(strength){}
/*
Enemy::Enemy(const sf::Texture& temp) {
	/*sprite.setSize(sf::Vector2f(32.0f, 32.0f));
	sprite.setOrigin(sprite.getSize() / 2.0f);
	sprite.setTexture(&temp);
	sprite.setPosition(800, 350);

	rect = sf::IntRect(64, 64, 32, 32);
	sprite.setTextureRect(rect);
	animation = CharacterAnimation(rect, sf::seconds(0.125));
	velocity = sf::Vector2f(0.0f, 0.0f);
	*//*
	sf::IntRect i (64, 64, 32, 32);
	sprite.setTexture(&temp);
	sprite.setTextureRect(i);
	sprite.setPosition(800, 350);
	animation.setRect(i);
	setHealth(100.0);
	setSpeed(2.f, sf::seconds(2.2 * 0.125));
	setJumpHeight(10.20);
	setCanJump(true);
	setOnAir(false);
	setCanClimb(false);

	atackSpeed = 0.5f;
	strength = 1.5f;
}
*/
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

void Enemy::refresh(const Player& player, bool wall) {

	if (player.getPosition().x >= getPosition().x) {
		velocity.x++;
		//animation.rotateSprite(sprite, 'r');
		moveRight();
	}
	else if (player.getPosition().x < getPosition().x) {
		velocity.x--;
		//animation.rotateSprite(sprite, 'l');
		moveLeft();
	}
	Character::refresh();
	// AI SECTION
	if (wall) {
		jump();
	}
	else if ((abs(player.getPosition().x - getPosition().x) < 30 && (player.getPosition().y < getPosition().y))) {
		jump();
	}

}


