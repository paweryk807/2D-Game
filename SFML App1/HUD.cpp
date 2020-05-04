#include "HUD.h"

HUD::HUD(float value) {
	try{
		loadTexture(HEARTS_PATH);
		this->value = value;
		previous = value;
		sf::IntRect rect(sf::Vector2i(0, 0), sf::Vector2i(17, 17));
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		sprite.setPosition(1150, 620);
		sprite.setScale(4, 4);
		font.loadFromFile(FONT_PATH);
		playerStats.setFont(font);
		playerStats.setPosition(920, 600);
		playerStats.setFillColor(sf::Color::Magenta);
		playerStats.setString("STATS");
		sf::Vector2f factors(0.75, 0.75);
		playerStats.setScale(factors);
		playerStats.setOutlineThickness(0.15f);
		playerStats.setOutlineColor(sf::Color::Black);
		time = playerStats;
		time.setCharacterSize(35);

		gameStats = playerStats; 
		time.setPosition(130.f, 620.f);
		gameStats.setPosition(130, 40.0f);
		gameStats.setCharacterSize(40);
		gameStats.setFillColor(sf::Color::Color(12,12,31,123));
		gameStats.setOutlineColor(sf::Color::Cyan);
	}
	catch(std::exception e) {
		std::cout << e.what() << std::endl;
	}
}

bool HUD::update(Player* player, Timer* timer, unsigned int round, unsigned int score)
{
	float current = player->getHealth();
	playerStats.setString("Experience : " + std::to_string((int)player->getExp()) + 
						"\nLevel : " + std::to_string(player->getLevel()) +
						"\nHealth : " + std::to_string((int)current) + "/" + std::to_string((int)player->getMaxHP()) + 
						"\nStrength : " + std::to_string(player->getStrength()).substr(0, 4) +
						"\nSpeed : " + std::to_string(player->getSpeed()).substr(0, 4));
	playerStats.setCharacterSize(30);
	time.setString(timer->getTimeString());
	gameStats.setString("Round: " + std::to_string(round) + "\nScore: " + std::to_string(score));
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

bool HUD::loadTexture(std::string text) {
	if (!texture.loadFromFile(text)) {
		throw std::exception("HUD Texture error!");
		return false;
	}
	return true;
}

bool HUD::setValue(float v) {
	if(v >= 0) {
		value = v;
	}
	return (v >= 0);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates) const {
	target.draw(playerStats);
	target.draw(sprite);
	target.draw(gameStats);
	target.draw(time);
}
sf::Sprite HUD::getSpite() {
	return sprite;
}

sf::Text& HUD::getText() {
	return playerStats;
}