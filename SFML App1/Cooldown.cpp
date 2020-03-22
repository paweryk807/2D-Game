#include "Cooldown.h"

Cooldown::Cooldown(sf::Time t) {
	time = t;
}

bool Cooldown::elapsed() {
	if (clock.getElapsedTime() > time) {
		return true;
	}
	return false;
}

void Cooldown::setCooldown(sf::Time t) {
	time = t;
}

void Cooldown::restartCooldown() {
	clock.restart();
}

sf::Time Cooldown::getTime() {
	return time;
}

sf::Clock Cooldown::getClock() {
	return clock;
}