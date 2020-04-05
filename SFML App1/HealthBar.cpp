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
		font.loadFromFile(FONT_PATH);
		playerStats.setFont(font);
		playerStats.setPosition(1500, 960);
		playerStats.setFillColor(sf::Color::Magenta);
		playerStats.setString("STATS");
		sf::Vector2f factors(1.f, 1.f);
		playerStats.setScale(factors);
		playerStats.setOutlineThickness(0.15f);
		playerStats.setOutlineColor(sf::Color::Black);
	/*	playerHP.setFont(font);
		playerHP.setPosition(1770, 940);
		playerExp.setFont(font);
		playerExp.setPosition(1800, 940);
		playerLevel.setFont(font);
		playerLevel.setPosition(1830, 940);
	*/
		//anim.setRect(rect); //Default texture size
	}
	catch(std::exception e) {
		std::cout << e.what() << std::endl;
	}
}
/* sf::Text object;
    std::string round = "Round : ";// + static_cast<char>(number);
    round += std::to_string(number);
    object.setString(round);
    sf::Vector2f factors(1.f, 1.f);  
    sf::Font font;
    font.loadFromFile(FONT_PATH);
    object.setFont(font);
    object.setFillColor(sf::Color::Magenta);
    object.setScale(factors);
    object.setOutlineThickness(0.5f);
    object.setOutlineColor(sf::Color::White);
    object.setPosition(sf::Vector2f(WIDTH/2 - (round.length()+1.5f) *10, ((HEIGHT/2)/6))); // /6 dla symetrii*/

bool HealthBar::update(Player* player)
{
	float current = player->getHealth();
	playerStats.setString("Experience : " + std::to_string((int)player->getExp()) + "\nLevel : " + std::to_string(player->getLevel()) + "\nHealth : "  
		+ std::to_string((int)current) + "/" + std::to_string((int)player->getMaxHP()));

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

void HealthBar::draw(sf::RenderWindow* window) {
	window->draw(playerStats);
	window->draw(sprite);
}
sf::Sprite HealthBar::getSpite() {
	return sprite;
}

sf::Text& HealthBar::getText() {
	return playerStats;
}