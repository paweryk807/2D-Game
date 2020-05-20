#pragma once
#include <time.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Bird.h"
#include "Menu.h"
#include "Functions.h"
#include "Map.h"
#include "HUD.h"
#include "EnemySpawner.h"
#include "PlayerHandler.h"
#include "Functions.h"
class Game {
	/*
	Jest to glowna klasa programu, obsluguje ona gre i wyswietlanie menu.
	*/
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Map> level;
	PlayerHandler playerHandler;
	Bird bonusBird;
	HUD hud;
	EnemySpawner spawner;
	Menu menu;
	bool started;
	bool pause;

	unsigned int round;
	unsigned int score;

public:
	Game();
	/* Metoda manipulujaca statystykami gracza w zaleznosci od typu bonusu */
	bool addBonus(Bird bonusBird);
	/* Obsluga zdarzen zwiazanych z obiektami typu soldier. W metodzie tej 
	sprawdzane jest, czy zaden z przeciwnikow tego typu nie koliduje z mapa 
	oraz czy nie zostal on postrzelony przez gracza, czy tez sam go nie postrzelil.*/
	void soldierHandler(bool& killed);
	/* Metoda ma za zadanie obsluzyc wszystkie zdarzenia zwiazane z przeciwnikiem drona */
	void droneHandler(bool& killed);
	/* Obsluga obiektu latajacego na ekranie ptaka */
	void birdHandler(bool& shot);
	/* Metoda odpowiedzialna na ustawienie odpowiednich parametrow obiektow, gdy gra jest zrestartowana */
	void restart();
	/* Metoda wykonywana do inicjacji gry */
	void run();
	/* Metoda ktora planowo ma byc wykorzystywana do zmienienia poziomu, na ktorym gra gracz. 
	Program jest do tego przygotowany, lecz nie jest to wykorzystywane */
	void generateLevel();
	/* Metoda obslugujaca wydarzenia, gdy postac gracza zginie. Wywolywany jest tu obraz z napisem "Game Over" trwa on 3 sekundy */
	void gameOver();
	/*Glowna metoda programu, obsluguje cala gre. W zaleznosci od stanu gry wywoluje ona konkretne metody klasy Game oraz zarzadza wszystkimi 
	innymi obiektami nalezacymi do tej klasy. */
	void start();

	~Game();
};