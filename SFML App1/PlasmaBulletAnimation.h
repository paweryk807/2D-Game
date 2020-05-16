#pragma once
#include "Animation.h"
class PlasmaBulletAnimation : public Animation
{
	/* 
	Klasa animacji postaci drona 
	*/
public:
	/* Metoda odpowiedzialna za wszystkie animacje postaci */
	bool changeMove(int width, int leftStart, int leftEnd, int startHeight, sf::CircleShape& sprite); //width - szerokosc tekstury leftStart - pozycja startowa z pliku , leftEnd - koncowa
};
