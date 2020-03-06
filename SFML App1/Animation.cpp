#include "Animation.h"

Animation::Animation(sf::IntRect rect, sf::Time time) : rect(rect), animTime(time) {}
bool Animation::oX(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite)
{
	if (rect != sf::IntRect(0, 0, 0, 0)) {
		if (animClock.getElapsedTime() > animTime) {
			if (rect.left >= leftEnd) {
				rect.left = leftStart;
			}
			sprite.setTextureRect(rect);
			rect.left += width;
			animClock.restart();
		}
		return 1;
	}
	return 0;
}

bool Animation::oY(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite)
{
	if (rect != sf::IntRect(0, 0, 0, 0)) {
		if (animClock.getElapsedTime() > animTime) {
			if (rect.left <= leftStart || rect.left >= leftEnd) {
				rect.left = 19 * width;
			}
			sprite.setTextureRect(rect);
			rect.left += width;
			animClock.restart();
		}
		return 1;
	}
	return 0;
}

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
	this->animTime = animT;
}

void Animation::setRect(sf::IntRect rect) {
	this->rect = rect;
}

Animation::~Animation() {}