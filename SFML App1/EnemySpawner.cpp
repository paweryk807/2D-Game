#include "EnemySpawner.h"

EnemySpawner::EnemySpawner() : EnemySpawner(std::chrono::seconds(10)) {}
EnemySpawner::EnemySpawner(std::chrono::seconds seconds) : timer(seconds) {}

Timer& EnemySpawner::getTimer()
{
	return timer;
}

void EnemySpawner::setTime(std::chrono::seconds seconds) {
	timer.setTime(seconds);
}

void EnemySpawner::spawnPlasmaDrone(int value, int round) {
	int enemiesToSpawn = round / 5; // 1 ekstra co 5 rund
	drones.clear();
	dronesBullets.clear();
	for (int i = 0; i < enemiesToSpawn; i++) {
		dronesBullets.push_back(std::vector<std::unique_ptr<PlasmaBullet>>());
		for (int y = 0; y < 10; y++) {
			dronesBullets[i].push_back(std::unique_ptr<PlasmaBullet>(new PlasmaBullet(sf::Vector2f(2000, 2000), 3.f + 0.25f * y)));
		}
		drones.push_back(std::unique_ptr<PlasmaDrone>(new PlasmaDrone(dronesBullets[i])));
		//drones[i]->correctPosition(sf::Vector2f(utils::randomInt(0, 1200), 570 + utils::randomInt(-100, 0))); 
	}

	timer.start();
}

void EnemySpawner::spawnSoldiers(int value, int type)
{
	soldiers.clear();
	soldiers.reserve(value);
	std::vector<std::string> tmp;
	for (int i = 0; i < value; i++) {
		tmp.clear();
		/*  RANDOM TYPE SET  */
		//int type = std::rand() % 4;
		switch (type) {
		case 0: //BLUE
			tmp = { "images/Blue/Gunner_Blue_Idle.png", "images/Blue/Gunner_Blue_Run.png", "images/Blue/Gunner_Blue_Jump.png", "images/Blue/Gunner_Blue_Death.png" };
			break;
		case 1: //RED
			tmp = { "images/Red/Gunner_Red_Idle.png", "images/Red/Gunner_Red_Run.png", "images/Red/Gunner_Red_Jump.png", "images/Red/Gunner_Red_Death.png" };
			break;
		case 2: //YELLOW
			tmp = { "images/Yellow/Gunner_Yellow_Idle.png", "images/Yellow/Gunner_Yellow_Run.png", "images/Yellow/Gunner_Yellow_Jump.png", "images/Yellow/Gunner_Yellow_Death.png" };
			break;
		case 3: //GREEN
			tmp = { "images/Green/Gunner_Green_Idle.png", "images/Green/Gunner_Green_Run.png", "images/Green/Gunner_Green_Jump.png", "images/Green/Gunner_Green_Death.png" };
			break;
		default:
			throw std::exception("Bad enemy type param.");
			break;
		}
		soldiers.push_back(std::unique_ptr<Soldier>(new Soldier(tmp)));
		soldiers[i]->correctPosition(sf::Vector2f(120 + utils::randomFloat(0, 200), 570 + utils::randomFloat(-50, 50))); 
		soldierBullets.push_back(std::unique_ptr<Bullet>(new Bullet(soldiers[i]->getPosition(), 11.f)));
		soldiers[i]->addAmmunition(*soldierBullets[soldierBullets.size() - 1]);

		timer.start();
	}
}

void EnemySpawner::levelUpEnemies(int round) {
	for (auto& elem : soldiers) {
		elem->levelUp(round);
	}
}