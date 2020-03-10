#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "CharacterAnimation.h"
class Player
{
private:
	sf::RectangleShape sprite; 
	sf::Vector2f velocity;
	sf::IntRect rect;
	CharacterAnimation animation;
	float speed;
	bool onAir;
	bool canJump;
	float jumpHeight;
public:	

		bool canClimb;

	Player() = default;
	Player(const sf::Texture& temp);
	~Player();

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

