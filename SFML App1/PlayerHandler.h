#pragma once
#include "Player.h"
#include "bullet.h"
#include "Bird.h"
#include "Utils.h"
class PlayerHandler
{
	void playerUpdater();
public:

	Player player;

	PlayerHandler();
	~PlayerHandler() = default;

	//bool addBonus(Bird bonusBird);
	void getActionFromUser();

	//void addAmmo();

	//void refresh();
};
