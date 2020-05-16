#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include "character.h"
#include "Cooldown.h"
#include "Utils.h"

class Bullet : public sf::Drawable
{
	/*
	Klasa standardowej wersji pocisku
	*/
	void setVelocity(sf::Vector2f vel);
protected:
	bool used;
	Cooldown cooldown;
	/* Zmienna odpowiedzialna za kolizje pocisku */
	sf::RectangleShape colid;
	sf::Vector2f velocity;
	sf::CircleShape sprite;

public:
	/*Metoda odpowiedzialna za rysowanie obiektu na ekranie*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;

	Bullet() = default;

	Bullet(sf::Vector2f startPos);

	Bullet(sf::Vector2f startPos, float speed);
	
	void setScale(sf::Vector2f scale);
	
	void setSize(float size);
	
	void setTime(sf::Time time);
	
	void setDirection(Character* character);
	/*
	Metoda zmieniajaca parametry pocisku w zaleznosci od przekazanego parametru
	obecnie wykorzystywana przy levelowaniu postaci
	*/
	void upgrade(int lvl);
	/*
	Metoda aktualizujaca polozenie pocisku  
	*/
	void refresh();
	/*
	Metoda restartujaca cooldown pocisku oraz ustawiajaca polozenie, z ktorego bedzie on zaczynal swoje przemieszczanie sie 
	*/
	void restart(sf::Vector2f pos);
	/*
	Metoda sprawdzajaca czy pocisk wpadl w kolizje z obiektem postaci
	*/
	bool hit(Character* character);
	
	void hide();
	
	void setUse(bool use);

	bool isUsed();
	
	sf::CircleShape getSprite();
	
	sf::Vector2f getVelocity();
	
	Cooldown getCooldown();
	
	Collider getCollider();

	~Bullet() = default;
};
