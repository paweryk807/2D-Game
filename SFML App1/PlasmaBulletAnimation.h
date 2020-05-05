#pragma once
#include "Animation.h"
class PlasmaBulletAnimation : public Animation
{
public:
	bool changeMove(int width, int leftStart, int leftEnd, int startHeight, sf::CircleShape& sprite); //width - szerokosc tekstury leftStart - pozycja startowa z pliku , leftEnd - koncowa 
};

