#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>
class CharacterAnimation : public Animation {

public:
	CharacterAnimation() = default ;
	CharacterAnimation(sf::IntRect rect, sf::Time time);
	
	bool changeMove(int width, int leftStart, int leftEnd, int startHeight, sf::RectangleShape& sprite); //width - szerokosc tekstury leftStart - pozycja startowa z pliku , leftEnd - koncowa 
	//bool oY(int width, int leftStart, int leftEnd, int startHeight, sf::RectangleShape& sprite);
	//bool idle(int width, int leftStart, int leftEnd, int startHeight, sf::RectangleShape& sprite);
	bool jump(int width, int leftStart, int leftEnd, int startHeight, sf::RectangleShape& sprite,  sf::Vector2f& velocity);
	bool death(int width, int leftStart, int leftEnd, int startHeight, sf::RectangleShape& sprite,  sf::Vector2f& velocity);
	~CharacterAnimation();
};

