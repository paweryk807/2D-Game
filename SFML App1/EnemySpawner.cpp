#include "EnemySpawner.h"

EnemySpawner::EnemySpawner() : EnemySpawner(std::chrono::seconds(10)) {
	loadTextureHandler();
}
EnemySpawner::EnemySpawner(std::chrono::seconds seconds) : timer(seconds) {
	loadTextureHandler();
}

Timer& EnemySpawner::getTimer()
{
	return timer;
}

void EnemySpawner::setTime(std::chrono::seconds seconds) {
	timer.setTime(seconds);
}

void EnemySpawner::spawnPlasmaDrone(int value, int round) {
	/* Zwiekszanie ilosci wrogow co 5 rund */
	int enemiesToSpawn = round / 5; 
	drones.clear();
	dronesBullets.clear();
	for (int i = 0; i < enemiesToSpawn; i++) {
		dronesBullets.push_back(std::vector<std::unique_ptr<PlasmaBullet>>());
		for (int y = 0; y < 10; y++) {
			dronesBullets[i].push_back(std::unique_ptr<PlasmaBullet>(new PlasmaBullet(sf::Vector2f(2000, 2000), 3.f + 0.25f * y)));
		}
		drones.push_back(std::unique_ptr<PlasmaDrone>(new PlasmaDrone(dronesBullets[i], plasmaDrone)));
	}

	timer.start();
}
/* Metoda przyjmuje pusty vector vec, rezerwuje ilosc pamieci dla vec oraz wczytuje tekstury z plikow przekazanych przez wektor str do wektora vec */
bool EnemySpawner::loadFromFile(std::vector<sf::Texture>& vec, std::vector<std::string>& str) {
	vec.reserve(str.size());
	int i = 0;
	for (auto elem : str) {
		vec.push_back(sf::Texture());
		if (!(vec[i].loadFromFile(elem))) {
			return 0;
		}
		i++;
	}
	return 1;
}

void EnemySpawner::loadTextureHandler() {
	std::vector<std::string> tmp;
	//Blue
	tmp = { "images/Blue/Gunner_Blue_Idle.png", "images/Blue/Gunner_Blue_Run.png", "images/Blue/Gunner_Blue_Jump.png", "images/Blue/Gunner_Blue_Death.png" };
	if(!loadFromFile(blueSoldier, tmp)) throw std::exception("Soldier Texture error!");
	//Red
	tmp = { "images/Red/Gunner_Red_Idle.png", "images/Red/Gunner_Red_Run.png", "images/Red/Gunner_Red_Jump.png", "images/Red/Gunner_Red_Death.png" };
	if (!loadFromFile(redSoldier, tmp)) throw std::exception("Soldier Texture error!");
	//Yellow
	tmp = { "images/Yellow/Gunner_Yellow_Idle.png", "images/Yellow/Gunner_Yellow_Run.png", "images/Yellow/Gunner_Yellow_Jump.png", "images/Yellow/Gunner_Yellow_Death.png" };
	if (!loadFromFile(yellowSoldier, tmp)) throw std::exception("Soldier Texture error!");
	//Green
	tmp = { "images/Green/Gunner_Green_Idle.png", "images/Green/Gunner_Green_Run.png", "images/Green/Gunner_Green_Jump.png", "images/Green/Gunner_Green_Death.png" };
	if (!loadFromFile(greenSoldier, tmp)) throw std::exception("Soldier Texture error!");
	//Drone
	tmp = { "images/PlasmaDrone/explode_sheet.png","images/PlasmaDrone/fire_sheet.png","images/PlasmaDrone/idle_sheet.png" };
	if (!loadFromFile(plasmaDrone, tmp)) throw std::exception("Drone Texture error!");
}

void EnemySpawner::spawnSoldiers(int value, int type)
{
	soldiers.clear();
	soldiers.reserve(value);
	std::vector<std::string> tmp;
	for (int i = 0; i < value; i++) {
		tmp.clear();
		/*  RANDOM TYPE SET  */
		switch (type) {
		case 0: //BLUE
			soldiers.push_back(std::unique_ptr<Soldier>(new Soldier(blueSoldier)));
			soldiers[i]->correctPosition(sf::Vector2f(120 + utils::randomFloat(0, 200), 570 + utils::randomFloat(-50, 50)));
			soldierBullets.push_back(std::unique_ptr<Bullet>(new Bullet(soldiers[i]->getPosition(), 11.f)));
			soldiers[i]->addAmmunition(*soldierBullets[soldierBullets.size() - 1]);
		//	tmp = { "images/Blue/Gunner_Blue_Idle.png", "images/Blue/Gunner_Blue_Run.png", "images/Blue/Gunner_Blue_Jump.png", "images/Blue/Gunner_Blue_Death.png" };
			break;
		case 1: //RED
			soldiers.push_back(std::unique_ptr<Soldier>(new Soldier(redSoldier)));
			soldiers[i]->correctPosition(sf::Vector2f(120 + utils::randomFloat(0, 200), 570 + utils::randomFloat(-50, 50)));
			soldierBullets.push_back(std::unique_ptr<Bullet>(new Bullet(soldiers[i]->getPosition(), 11.f)));
			soldiers[i]->addAmmunition(*soldierBullets[soldierBullets.size() - 1]);
		//	tmp = { "images/Red/Gunner_Red_Idle.png", "images/Red/Gunner_Red_Run.png", "images/Red/Gunner_Red_Jump.png", "images/Red/Gunner_Red_Death.png" };
			break;
		case 2: //YELLOW
			soldiers.push_back(std::unique_ptr<Soldier>(new Soldier(yellowSoldier)));
			soldiers[i]->correctPosition(sf::Vector2f(120 + utils::randomFloat(0, 200), 570 + utils::randomFloat(-50, 50)));
			soldierBullets.push_back(std::unique_ptr<Bullet>(new Bullet(soldiers[i]->getPosition(), 11.f)));
			soldiers[i]->addAmmunition(*soldierBullets[soldierBullets.size() - 1]);
		//	tmp = { "images/Yellow/Gunner_Yellow_Idle.png", "images/Yellow/Gunner_Yellow_Run.png", "images/Yellow/Gunner_Yellow_Jump.png", "images/Yellow/Gunner_Yellow_Death.png" };
			break;
		case 3: //GREEN
			soldiers.push_back(std::unique_ptr<Soldier>(new Soldier(greenSoldier)));
			soldiers[i]->correctPosition(sf::Vector2f(120 + utils::randomFloat(0, 200), 570 + utils::randomFloat(-50, 50)));
			soldierBullets.push_back(std::unique_ptr<Bullet>(new Bullet(soldiers[i]->getPosition(), 11.f)));
			soldiers[i]->addAmmunition(*soldierBullets[soldierBullets.size() - 1]);
		//	tmp = { "images/Green/Gunner_Green_Idle.png", "images/Green/Gunner_Green_Run.png", "images/Green/Gunner_Green_Jump.png", "images/Green/Gunner_Green_Death.png" };
			break;
		default:
			throw std::exception("Bad enemy type param.");
			break;
		}
		/*
		soldiers.push_back(std::unique_ptr<Soldier>(new Soldier(tmp)));
		soldiers[i]->correctPosition(sf::Vector2f(120 + utils::randomFloat(0, 200), 570 + utils::randomFloat(-50, 50))); 
		soldierBullets.push_back(std::unique_ptr<Bullet>(new Bullet(soldiers[i]->getPosition(), 11.f)));
		soldiers[i]->addAmmunition(*soldierBullets[soldierBullets.size() - 1]);
		*/
		timer.start();
	}
}

void EnemySpawner::levelUpEnemies(int round) {
	for (auto& elem : soldiers) {
		elem->levelUp(round);
	}
}