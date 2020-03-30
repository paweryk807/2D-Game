#pragma once
#include "Animation.h"
class SoldierAnimation : public Animation
{
public:
	bool oX(sf::RectangleShape& sprite); //width - szerokosc tekstury leftStart - pozycja startowa z pliku , leftEnd - koncowa 
	bool idle(sf::RectangleShape& sprite);
	bool jump(sf::RectangleShape& sprite,const sf::Vector2f& velocity);
	bool death(sf::RectangleShape& sprite, sf::Vector2f& velocity);
};

