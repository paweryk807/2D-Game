#pragma once
#include <chrono>
#include <vector>
#include "Soldier.h"
#include "PlasmaDrone.h"
#include "bullet.h"
#include "Timer.h"


class EnemySpawner
{
private:
	Timer timer;
public:
	std::vector<Soldier*> soldiers;
	std::vector<PlasmaDrone*> drones;
	std::vector<Bullet*> soldierBullets;
	std::vector<Bullet*> dronesBullets;

	EnemySpawner();
	EnemySpawner(std::chrono::seconds seconds);
	Timer& getTimer();
	void setTime(std::chrono::seconds seconds);
	void spawnSoldiers(int value, int type);
//	void spawnPlasmaDrone(int value, int type);
	void levelUpEnemies(int round);
	~EnemySpawner() = default;
};