#pragma once
#include<chrono>
#include"SFML/Graphics.hpp"

#define TIME_FONT_PATH  "fonts/Schaeffer.ttf"

class Timer {
	sf::Font font;
	sf::Text timeLeft;
	std::chrono::seconds time; // Na runde 
	std::chrono::steady_clock::time_point begin;

public:		
	void setBegin();

	Timer() = delete;
	Timer(std::chrono::seconds seconds);
	friend class EnemySpawner;
	void refresher() noexcept;
	void drawTimer(sf::RenderWindow* window) const noexcept;
	bool elapsed();

};

