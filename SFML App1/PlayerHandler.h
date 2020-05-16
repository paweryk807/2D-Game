#pragma once
#include "Player.h"
#include "bullet.h"
#include "Bird.h"
#include "Utils.h"
class PlayerHandler
{
	/* 
	Klasa odpowiedzialna za obsluge postaci gracza 
	Odbierane jest rowniez tutaj 
	sterowanie postacia - zapewnia obsluge postaci przez uzytkownika 
	*/

	/*
	W planach jest rozwiniecie mozliwosci tej klasy 
	*/
	void playerUpdater();
public:

	Player player;

	PlayerHandler();
	~PlayerHandler() = default;


	void getActionFromUser();

	//void addAmmo();

	//void refresh();
};
