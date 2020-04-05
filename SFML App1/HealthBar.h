#pragma once
#include"SFML/Graphics.hpp"
#include "Animation.h"
#include "Player.h"
#define HEARTS_PATH "images/heart_animated_2.png"
class HealthBar
{
	sf::Texture texture;
	sf::Sprite sprite;
	float value; // poczatkowa wartosc zycia ew. ulepszona 
	float previous;
public:
	HealthBar(float value);

	bool update(Player* player);

	bool loadTexture(std::string text);

	bool setValue(float v);

	sf::Sprite getSpite();

	~HealthBar() = default;
};

