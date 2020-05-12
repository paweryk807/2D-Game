#pragma once
#include<chrono>
#include"SFML/Graphics.hpp"

#define TIME_FONT_PATH  "fonts/Schaeffer.ttf"

class Timer {
	sf::String timeLeft;
	std::chrono::seconds time; // Na runde
	std::chrono::steady_clock::time_point begin;
	bool disabled;
	void setBegin();

public:

	Timer() = delete;
	Timer(std::chrono::seconds seconds);
	void setTime(std::chrono::seconds seconds) noexcept;
	void stop() noexcept;
	void start() noexcept;
	sf::String getTimeString();
	void refresher() noexcept;
	bool elapsed() noexcept;

	unsigned int getCountedTime();
	~Timer() = default;
};
