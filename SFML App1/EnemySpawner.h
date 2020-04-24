#pragma once
#include <chrono>
#include <vector>
#include "Soldier.h"
#include "bullet.h"

//ENEMY TYPES

class EnemySpawner
{
	std::chrono::seconds time; // Na runde 
	std::chrono::steady_clock::time_point begin;

public:
	std::vector<Soldier*> enemies;
	std::vector<Bullet*> bullets;


	EnemySpawner(std::chrono::seconds minutes);
	bool elapsed() const noexcept;
	void spawnEnemies(int value, int type);
	//std::vector<Soldier*>* getEnemies() const noexcept;
	//std::vector<Bullet*>* getBullets() const noexcept;

};