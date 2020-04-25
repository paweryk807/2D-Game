#pragma once
#include <chrono>
#include <vector>
#include "Soldier.h"
#include "bullet.h"
#include "Timer.h"


class EnemySpawner
{
private:
	Timer timer;
public:
	std::vector<Soldier*> enemies;
	std::vector<Bullet*> bullets;
	
	//void drawTimer(sf::RenderWindow* window) const noexcept;
	EnemySpawner();
	EnemySpawner(std::chrono::seconds seconds);
	Timer& getTimer();
	//bool elapsed() const noexcept;
	//void refresher() noexcept;

	void spawnEnemies(int value, int type);
	//std::vector<Soldier*>* getEnemies() const noexcept;
	//std::vector<Bullet*>* getBullets() const noexcept;

};