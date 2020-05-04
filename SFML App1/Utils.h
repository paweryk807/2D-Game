#pragma once
#include<random>
namespace utils {
	int randomInt(int from, int to);
	float randomFloat(float from, float to);

	enum class BonusType {
		strength, health, time, boost
	};

	enum class PlasmaDroneState {
		fire, fly, explode
	};
}