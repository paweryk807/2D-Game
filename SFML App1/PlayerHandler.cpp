#include "PlayerHandler.h"

PlayerHandler::PlayerHandler() : player("images/characters.png") {}

void PlayerHandler::getActionFromUser() {
	if (player.getCanClimb()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.moveUp();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.moveDown();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		player.shot();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player.moveLeft();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player.moveRight();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		player.jump();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		player.setSpeedToSprint();
	}
	else {
		player.setSpeedToWalk();
	}

	playerUpdater();
}

void PlayerHandler::playerUpdater()
{
	if (player.refresh())
	{
		for (auto& elem : player.bullets)
		{
			elem.upgrade(player.getLevel());
		}
	}
}