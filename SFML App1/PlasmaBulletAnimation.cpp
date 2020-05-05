#include "PlasmaBulletAnimation.h"

bool PlasmaBulletAnimation::changeMove(int width, int leftStart, int leftEnd, int startHeight, sf::CircleShape& sprite)
{
	if (rect != sf::IntRect(0, 0, 0, 0)) {
		rect.top = startHeight;
		if (animationCooldown.elapsed()) {
			if (rect.left >= leftEnd) {
				rect.left = leftStart;
				return 1;
			}
			sprite.setTextureRect(rect);
			rect.left += width;
			animationCooldown.restartCooldown();
		}
		return 0;
	}
	return 1;
}
