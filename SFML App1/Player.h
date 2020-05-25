#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "bullet.h"

class Player : public Character
{
private:
	float sprintSpeed;
	float walkSpeed;

	float exp;
	int level;
	int prevLevel;
	float strength;
	float maxHP;
	bool shield;
	sf::Texture texture;
	sf::RectangleShape shieldShape;
	sf::RectangleShape shieldCollider;
	Cooldown shotCooldown;
	/* Zmiana predkosci poruszania sie postaci gracza */
	void setSpeed(float temp, sf::Time tempAnim);


public:
	std::vector<Bullet> bullets;

	/* Sterowanie */
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void jump();
	bool shot();

	void setSpeedToSprint();
	void setSpeedToWalk();

	/* Resetowanie postaci */
	void reset();
	/* Aktualizacja */
	bool refresh();
	/* Rysowanie */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	/* Ustawienia postaci */

	void setWalkSpeed(float speed);

	void setLevel(int lvl);
	void setStrength(float str);
	void addExp(float nExp);
	/* Pobieranie stanu postaic */
	float getMaxHP();
	sf::RectangleShape getShield();
	Collider getShieldCollider();
	bool leveled();
	float getStrength();
	float getExp();
	bool getShieldState();
	void setShieldState(bool state);
	int getLevel();
	/* c-tory, d-tor */
	Player() = delete;
	Player(const std::string& temp);
	void loadTexture(const std::string& path);
	~Player() = default;
};
