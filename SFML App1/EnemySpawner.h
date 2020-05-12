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
	std::vector<std::unique_ptr<Soldier>> soldiers;
	std::vector<std::unique_ptr<PlasmaDrone>> drones;
	std::vector<std::unique_ptr<Bullet>> soldierBullets;
	std::vector<std::vector<std::unique_ptr<PlasmaBullet>>> dronesBullets;

	EnemySpawner();
	EnemySpawner(std::chrono::seconds seconds);
	Timer& getTimer();
	void setTime(std::chrono::seconds seconds);
	void spawnSoldiers(int value, int type);
	void spawnPlasmaDrone(int value, int round);
	void levelUpEnemies(int round);
	~EnemySpawner() = default;
};