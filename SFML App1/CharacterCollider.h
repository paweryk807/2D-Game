#pragma once
#include "Collider.h"
class CharacterCollider : public Collider {
public:
	CharacterCollider(sf::RectangleShape& body);
	bool checkCollision(Collider other, sf::Vector2f& direction, float push);
	~CharacterCollider() = default;
};

