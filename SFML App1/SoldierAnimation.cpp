#include "SoldierAnimation.h"

bool SoldierAnimation::oX(sf::RectangleShape& sprite)
{

	if (rect != sf::IntRect(0, 0, 0, 0)) {
		if (animationCooldown.elapsed()) {
			if (rect.left >= 239) {
				rect.left = 0;
			}
			sprite.setTextureRect(rect);
			rect.left += 48;
			animationCooldown.restartCooldown();
		}
		return 1;
	}
	return 0;

}

bool SoldierAnimation::death(sf::RectangleShape& sprite, sf::Vector2f& velocity)
{
	velocity.x = 0;
	velocity.y = 0;
	if (rect != sf::IntRect(0, 0, 0, 0)) {
		if (animationCooldown.elapsed()) {
			if (rect.left >= 335) {
				rect.left = 0;
			}
			sprite.setTextureRect(rect);
			rect.left += 48;
			animationCooldown.restartCooldown();
		}
		return 1;
	}
	return 0;

}

bool SoldierAnimation::idle(sf::RectangleShape& sprite)
{

	if (rect != sf::IntRect(0, 0, 0, 0)) {
		if (animationCooldown.elapsed()) {
			if (rect.left >= 191) {
				rect.left = 0;
			}
			sprite.setTextureRect(rect);
			rect.left += 48;
			animationCooldown.restartCooldown();
		}
		return 1;
	}
	return 0;

}

bool SoldierAnimation::jump(sf::RectangleShape& sprite, const sf::Vector2f& velocity)
{
	if (rect != sf::IntRect(0, 0, 0, 0)) {
		if (animationCooldown.elapsed()) {
			if (velocity.y > 0.0f) { // wznosi sie
				rect.left = 48;
			}
			else if (velocity.y <= 0.0f) { // bedzie zaraz opadac 
				rect.left = 0;

			}
			else rect.left = 0;
			sprite.setTextureRect(rect);	
			animationCooldown.restartCooldown();
		}
		return 1;
	}
	return 0;
}
