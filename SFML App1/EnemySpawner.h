#pragma once
#include <chrono>
#include <vector>
#include "Soldier.h"
#include "PlasmaDrone.h"
#include "bullet.h"
#include "Timer.h"

class EnemySpawner
{
	/*
	Klasa kierujaca tworzeniem obiektow przeciwnikow, trzyma rowniez zegar przechowujacy czas przeznaczony
	na pokonanie przeciwnikow 
	*/
private:

	/* Textures */
	void loadTextureHandler();
	bool loadFromFile(std::vector<sf::Texture>& vec, std::vector<std::string>& str);
	std::vector<sf::Texture> blueSoldier;
	std::vector<sf::Texture> redSoldier;
	std::vector<sf::Texture> yellowSoldier;
	std::vector<sf::Texture> greenSoldier;
	std::vector<sf::Texture> plasmaDrone;
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
	/* Metoda podnoszaca statystyki postaci zolnierzy */
	void levelUpEnemies(int round);
	
	~EnemySpawner() = default;
};