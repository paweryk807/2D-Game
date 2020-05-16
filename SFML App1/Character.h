#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include "CharacterAnimation.h"
#include "Collider.h"
#include "CharacterAnimation.h"

class Character : public sf::Drawable
{
private:
	float health;
	float speed;
	float jumpHeight;

	bool onAir;
	bool canJump;
	bool canClimb;

	void moveUp();
	void moveDown();
	void jump();
	void moveLeft();
	void moveRight();

protected:
	sf::RectangleShape sprite;
	sf::Vector2f velocity;
	CharacterAnimation animation;
	void setAnimation(CharacterAnimation& a);

public:	
	Character();
	~Character() = default;

	virtual void reset() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;

	float getHealth();
	float getSpeed();
	float getJumpHeight();

	bool getCanClimb();
	bool getCanJump();
	bool getOnAir();

	sf::RectangleShape getSprite() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;

	void setSprite(sf::RectangleShape& sprite);
	/* Metoda ustawiaj¹ca pozycjê w wyznaczonym obszarze (w parametrze przekazywany ma byc wektor z maksymalna szerokoscia x i y) */
	void correctPosition(sf::Vector2f);
	void setVelocity(sf::Vector2f vel);

	void setJumpHeight(float height);
	void setCanClimb(bool climb);
	void setHealth(float hp);

	void setCanJump(bool jump);
	void setOnAir(bool air);
	/* Metoda odswiezajaca   */
	void refresh();
	void onCollision(sf::Vector2f direction);
	void setSpeed(float temp);

	Collider getCollider();
};
