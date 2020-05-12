#include "Bird.h"

Bird::Bird() : Bird(utils::BonusType(utils::randomInt(0, 3)), sf::Vector2f(0.0, 0.0)) {};

Bird::Bird(sf::Vector2f start) : Bird(utils::BonusType(utils::randomInt(0, 3)), start) {};

Bird::Bird(utils::BonusType type, sf::Vector2f start) {
	try {
		changeDirection = 0;
		sprite.setPosition(start);
		bonus = static_cast<utils::BonusType>(type);
		texture.loadFromFile(BIRD_TEXTURE_PATH);
		sprite.setTexture(&texture);
		sf::IntRect rect(0, 16, 16, 16);
		sprite.setTextureRect(rect);
		animation.setRect(rect);
		sprite.setSize(sf::Vector2f(24, 24));
	}
	catch (std::exception e) {
		std::cerr << e.what();
	}
}

float Bird::receiveBonus() {
	switch (bonus) {
	case utils::BonusType::boost:
		return 2.0f;
		break;
	case utils::BonusType::health:
		return 50.0f;
		break;
	case utils::BonusType::strength:
		return 2.5f;
		break;
	case utils::BonusType::time:
		return 10.0f;
		break;
	default:
		return 0.0f;
	}
}

utils::BonusType Bird::getBonusType() {
	return bonus;
}

void Bird::fly(bool collision, bool shooted) {
	if (!collision) {
		if (shooted) {
			if (sprite.getPosition().y < 1200)
				velocity.y--;
		}
		else if (sprite.getPosition().y > 1200 || sprite.getPosition().y <= 450) {
			velocity.y++;
		}
		if (changeDirection) {
			animation.rotateSprite(sprite, 'l');
			velocity.x++;
		}
		else {
			animation.rotateSprite(sprite, 'r');
			velocity.x--;
		}
		if (sprite.getPosition().x <= 16) changeDirection = true;
		else if (sprite.getPosition().x >= 1264) changeDirection = false;
		animation.setAnimTime(sf::seconds(0.10));
		animation.changeMove(16, 0, 128, 16, sprite);
		sprite.move(velocity);
		velocity.y = 0;
		if (prevPos == sprite.getPosition()) {
			velocity.y++;
		}
		velocity.x = 0;
	}
	else {
		velocity.y++;
		animation.setAnimTime(sf::seconds(0.5));
	}
	prevPos = sprite.getPosition();
}

void Bird::reset() {
	bonus = static_cast<utils::BonusType>(utils::randomInt(0, 3));
}