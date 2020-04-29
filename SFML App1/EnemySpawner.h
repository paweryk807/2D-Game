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

	EnemySpawner();
	EnemySpawner(std::chrono::seconds seconds);
	Timer& getTimer();
	void setTime(std::chrono::seconds seconds);
	void spawnEnemies(int value, int type);
	~EnemySpawner() = default;
};