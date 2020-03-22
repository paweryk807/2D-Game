#include "CharacterAnimation.h"

CharacterAnimation::CharacterAnimation(sf::IntRect rect, sf::Time time) {
	setRect(rect); setAnimTime(time);
}

bool CharacterAnimation::oX(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite)
{
	if (rect != sf::IntRect(0, 0, 0, 0)) {
		if (animationCooldown.elapsed()) {
			if (rect.left >= leftEnd) {
				rect.left = leftStart;
			}
			sprite.setTextureRect(rect);
			rect.left += width;
			animationCooldown.restartCooldown();
		}
		return 1;
	}
	return 0;
}

bool CharacterAnimation::oY(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite)
{
	if (rect != sf::IntRect(0, 0, 0, 0)) {
		if (animationCooldown.elapsed()) {
			if (rect.left <= leftStart || rect.left >= leftEnd) {
				rect.left = 19 * width;
			}
			sprite.setTextureRect(rect);
			rect.left += width;
			animationCooldown.restartCooldown();
		}
		return 1;
	}
	return 0;
}

bool CharacterAnimation::jump(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite, sf::Vector2f velocity) {
	if (rect != sf::IntRect(0, 0, 0, 0)) {
		if (animationCooldown.elapsed()) {
			if (rect.left <= leftEnd) {
				if (velocity.y > 0.0f) { // wznosi sie
					rect.left = leftStart;
				}
				else if (velocity.y == 0.0f) { // bedzie zaraz opadac 
					rect.left += width;

				}
				else {
					rect.left += width;

				}
			}
			else {
				rect.left = leftStart;
			}
			sprite.setTextureRect(rect);
			animationCooldown.restartCooldown();
		}
		return 1;
	}
	return 0;
}



CharacterAnimation::~CharacterAnimation() {}