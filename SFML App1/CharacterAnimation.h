#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>
class CharacterAnimation : public Animation {

public:
	CharacterAnimation() = default ;
	CharacterAnimation(sf::IntRect rect, sf::Time time);
	
	bool oX(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite); //width - szerokosc tekstury leftStart - pozycja startowa z pliku , leftEnd - koncowa 
	bool oY(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite);
	bool jump(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite,  sf::Vector2f velocity);

	 
	~CharacterAnimation();
};

