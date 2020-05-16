#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>
class CharacterAnimation : public Animation {
	/*
	Klasa odpowiedzialna za animacje postaci
	*/
public:
	CharacterAnimation() = default;

	CharacterAnimation(sf::IntRect rect, sf::Time time);
	/* Metoda odpowiedzialna za animacje postaci, to znaczy ustawia ona wyswietlany fragment pliku */
	bool changeMove(int width, int leftStart, int leftEnd, int startHeight, sf::RectangleShape& sprite);
	/* Metoda odpowiedzialna za animacje skoku */
	bool jump(int width, int leftStart, int leftEnd, int startHeight, sf::RectangleShape& sprite, sf::Vector2f& velocity);
	/* Metoda odpowiedzialna za animacje smierci */
	bool death(int width, int leftStart, int leftEnd, int startHeight, sf::RectangleShape& sprite, sf::Vector2f& velocity);

	~CharacterAnimation();
};
