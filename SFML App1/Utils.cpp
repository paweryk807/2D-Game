#include "Utils.h"

int utils::randomInt(int from, int to)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution <int> dist(from, to);
	return dist(mt);
}

float utils::randomFloat(float from, float to)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(from, to);
	return dist(mt);
}