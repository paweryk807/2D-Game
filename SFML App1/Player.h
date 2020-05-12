#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "bullet.h"
//#include <memory>

//#define DEFAULT_PATH "images/Hero Knight/Sprites/Hero"//"images/characters.png"

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
	CharacterAnimation animation;
	sf::RectangleShape shieldShape;
	sf::RectangleShape shieldCollider;
	Cooldown shotCooldown;

	void setSpeed(float temp, sf::Time tempAnim);
	void setAnimation(CharacterAnimation& a);

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
	Player(const std::string& temp);//, std::vector<std::unique_ptr<Bullet>> bullets);//, std::vector< std::pair < Bullet, bool >> bullets);
	~Player() = default;
};
