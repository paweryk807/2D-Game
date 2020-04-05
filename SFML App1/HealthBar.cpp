#include "HealthBar.h"

HealthBar::HealthBar(float value) {
	try{
		loadTexture(HEARTS_PATH);
		this->value = value;
		previous = value;
		//anim.setAnimTime(sf::seconds(0.125f));
		sf::IntRect rect(sf::Vector2i(0, 0), sf::Vector2i(17, 17));
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		sprite.setPosition(1800, 980);
		sprite.setScale(4, 4);

		//anim.setRect(rect); //Default texture size
	}
	catch(std::exception e) {
		std::cout << e.what() << std::endl;
	}
}

bool HealthBar::update(Player* player)
{
	float current = player->getHealth();
	sf::IntRect rect = this->sprite.getTextureRect();
	if (current != previous) {
		previous = current;
		if (current >= value) {
			rect.left = 0;
		}
		else if (current >= 0.75f * value) {
			rect.left = 17;
		}
		else if (current >= 0.5f * value) {
			rect.left = 34;
		}
		else if (current > 0) {
			rect.left = 51;
		}
		else {
			rect.left = 68;
			return false;
		}
	}
	sprite.setTextureRect(rect);
	return false;
}

bool HealthBar::loadTexture(std::string text) {
	if (!texture.loadFromFile(text)) {
		throw std::exception("HealthBar Texture error!");
		return false;
	}
	return true;
}

bool HealthBar::setValue(float v) {
	if(v >= 0) {
		value = v;
	}
	return (v >= 0);
}

sf::Sprite HealthBar::getSpite() {
	return sprite;
}
