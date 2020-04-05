#pragma once
#include"SFML/Graphics.hpp"
#include "Animation.h"
#include "Player.h"
#define HEARTS_PATH "images/heart_animated_2.png"
#define FONT_PATH  "fonts/Schaeffer.ttf"
class HealthBar
{
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Text playerStats;
	sf::Font font;

	/*sf::Text playerLevel;
	sf::Text playerExp;
	sf::Text playerHP;*/
	float value; // poczatkowa wartosc zycia ew. ulepszona 
	float previous;

public:
	HealthBar(float value);

	bool update(Player* player);

	bool loadTexture(std::string text);

	bool setValue(float v);

	void draw(sf::RenderWindow* window);

	sf::Sprite getSpite();

	sf::Text& getText();

	~HealthBar() = default;
};

