#pragma once
#include"Character.h"
#include"Utils.h"
#define BIRD_TEXTURE_PATH "images/Bird/BirdSprite.png"
class Bird : public Character // mozna by zrobic dziedziczenie private
{
	utils::BonusType bonus;
	CharacterAnimation animation;
	bool changeDirection;
	sf::Texture texture;
	sf::Vector2f prevPos;
public:
	Bird();
	Bird(sf::Vector2f start);
	Bird(utils::BonusType type, sf::Vector2f start);
	float receiveBonus();
	utils::BonusType getBonusType();
	void fly(bool collision, bool shooted); // przy wywolaniu wrzucac kolizjê mapy
	void reset();
	~Bird() = default;
};
