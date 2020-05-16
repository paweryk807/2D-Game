#pragma once
#include"SFML/Graphics.hpp"
#include "Animation.h"
#include "Player.h"
#include "Timer.h"
#define HEARTS_PATH "images/heart_animated_2.png"
#define FONT_PATH  "fonts/Schaeffer.ttf"
class HUD : public sf::Drawable
{
	/*
	Klasa odpowiedzialna za wyswietlanie na ekranie statystyk postaci gracza, statystyk gry, 
	osiagnietego wyniku oraz czasu pozostalego do konca rundy.
	*/
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Font font;

	sf::Text playerStats;
	sf::Text gameStats;
	sf::Text time;

	float value; // poczatkowa wartosc zycia ew. ulepszona
	float previous;

public:
	HUD(float value);
	/* Metoda odpowiedzialna za aktualizacje wyswietlanych parametrow */
	bool update(Player* player, Timer* time, unsigned int round, unsigned int score);
	/* Wczytywanie textury serduszka obrazujacego stan zdrowia postaci gracza */
	bool loadTexture(std::string text);
	/* Metoda ustawiajaca wartosc zycia gracza wyswietlana na ekranie <- od niej zalezny jest obraz wyswietlanego serduszka */
	bool setValue(float v);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;

	sf::Sprite getSpite();

	sf::Text& getText();

	~HUD() = default;
};
