#pragma once
#include <chrono>
#include <vector>
#include "Soldier.h"
#include "bullet.h"

//ENEMY TYPES
std::vector<std::string> TYPE_0{ "images/Blue/Gunner_Blue_Idle.png", "images/Blue/Gunner_Blue_Run.png", "images/Blue/Gunner_Blue_Jump.png", "images/Blue/Gunner_Blue_Death.png" };
std::vector<std::string> TYPE_1{ "images/Red/Gunner_Red_Idle.png", "images/Red/Gunner_Red_Run.png", "images/Red/Gunner_Red_Jump.png", "images/Red/Gunner_Red_Death.png" };
std::vector<std::string> TYPE_2{"images/Yellow/Gunner_Yellow_Idle.png", "images/Yellow/Gunner_Yellow_Run.png", "images/Yellow/Gunner_Yellow_Jump.png", "images/Yellow/Gunner_Yellow_Death.png"};
std::vector<std::string> TYPE_3{"images/Green/Gunner_Green_Idle.png", "images/Green/Gunner_Green_Run.png", "images/Green/Gunner_Green_Jump.png", "images/Green/Gunner_Green_Death.png"};

class EnemySpawner
{
	static std::chrono::minutes time; // Na runde 
	std::chrono::steady_clock::time_point begin;
	static std::vector<Soldier> enemies;
	static std::vector<Bullet*> bullets;
public:
	EnemySpawner(std::chrono::minutes minutes);
	bool const elapsed() noexcept;
	void spawnEnemies(int value, int type);

};