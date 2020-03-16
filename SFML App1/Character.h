#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "CharacterAnimation.h"
class Character
{
private:
	float health;
	float speed;
	float jumpHeight;
	bool onAir;
	bool canJump;
	bool canClimb;
protected:
	sf::RectangleShape sprite; 
	sf::Vector2f velocity;
	sf::IntRect rect;
	CharacterAnimation animation;


public:	
	Character() = default;
	Character(const sf::Texture& temp);  // TU POWSTAJE DEFAULTOWA POSTAC :) 
	~Character();

	bool getCanClimb();
	float getHealth();
	bool getCanJump();
	bool getOnAir();
	float getSpeed();
	float getJumpHeight();
	
	void setJumpHeight(float height);
	void setCanClimb(bool climb);
	void setHealth(float hp);
	void setCanJump(bool jump);
	void setOnAir(bool air);
	void setSpeed(float, sf::Time);

	void moveUp();
	void jump();
	void moveDown();
	void moveLeft();
	void moveRight();
	void refresh();
	void onCollision(sf::Vector2f direction);
	void correctPosition(sf::Vector2i);
	sf::Vector2f getPosition() const;
	sf::RectangleShape getSprite() const;
	Collider getCollider();
};

