#pragma once
#include"Character.h"
#include"Utils.h"
#define BIRD_TEXTURE_PATH "images/Bird/BirdSprite.png"
class Bird : public Character 
{
	/*
	Klasa obiektu ptaka, ktory daje bonusy w grze
	*/
	utils::BonusType bonus;
	bool changeDirection;
	sf::Texture texture;
	sf::Vector2f prevPos;
public:
	
	Bird();
	
	Bird(sf::Vector2f start);
	
	Bird(utils::BonusType type, sf::Vector2f start);
	/*Metoda zwracajaca wartosc bonusu*/
	float receiveBonus(); 
	/*Metoda zwracajaca typ bonusu*/
	utils::BonusType getBonusType();
	/*Metoda odpowiedzialna za poruszanie sie ptaka*/
	void fly(bool collision, bool shot); 
	/*Metoda ustawiajaca losowy bonus dawany przez ptaka*/
	void reset();
	
	~Bird() = default;
};
