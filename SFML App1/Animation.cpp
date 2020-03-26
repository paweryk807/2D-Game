#include "Animation.h"

Animation::Animation(sf::IntRect& rect, sf::Time time) : rect(rect), animationCooldown(time) {}

bool Animation::rotateSprite(sf::RectangleShape& sprite, const char& direction) {
	if (sprite.getScale() != sf::Vector2f(1, 1) && direction == 'r') {
		sprite.setScale(sf::Vector2f(1, 1));
		return 1;
	}
	else if (sprite.getScale() != sf::Vector2f(-1, 1) && direction == 'l') {
		sprite.setScale(sf::Vector2f(-1, 1));
		return 1;
	}
	return 0;
}

void Animation::setAnimTime(sf::Time animT) {
	animationCooldown.setCooldown(animT);
}

void Animation::setRect(sf::IntRect& rect) {
	this->rect = rect;
}

void Animation::restartCooldown() {
	animationCooldown.restartCooldown();
}

sf::Time Animation::getAnimTime() {
	return animationCooldown.getTime();
}

sf::IntRect Animation::getRect() {
	return rect;
}

Cooldown Animation::getAnimationCooldown() {
	return animationCooldown;
}

Animation::~Animation() {}