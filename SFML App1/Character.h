#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "CharacterAnimation.h"
class Character
{
private:
	sf::RectangleShape sprite; 
	sf::Vector2f velocity;
	sf::IntRect rect;
	CharacterAnimation animation;
	float health;
	float speed;
	float jumpHeight;
	bool onAir;
	bool canJump;
	bool canClimb;

public:	
	Character() = default;
	Character(const sf::Texture& temp);
	~Character();

	bool getCanClimb();
	float getHealth();
	bool getCanJump();
	bool getOnAir();
	
	void setCanClimb(bool climb);
	void setHealth(float hp);
	void setCanJump(bool jump);
	void setOnAir(bool air);

	void moveUp();
	void jump();
	void moveDown();
	void moveLeft();
	void moveRight();
	void refresh();
	void onCollision(sf::Vector2f direction);
	void setSpeed(float, sf::Time);
	void correctPosition(sf::Vector2i);
	sf::Vector2f getPosition() const;
	sf::RectangleShape getSprite() const;
	Collider getCollider();
};

