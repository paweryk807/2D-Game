#include "Timer.h"
Timer::Timer(std::chrono::seconds seconds) {
	time = seconds;
	begin = std::chrono::steady_clock::now();
	timeLeft = ("Left :\n" + std::to_string(time.count()) + " seconds\nto kill all enemies");
	disabled = false;
}

void Timer::setTime(std::chrono::seconds seconds) noexcept {
	setBegin();
	time = seconds;
	timeLeft = ("Left :\n" + std::to_string(time.count()) + " seconds\nto kill all enemies");
}

std::chrono::seconds Timer::getTime() {
	return time;
}
void Timer::refresher() noexcept {
	if (!disabled) {
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		timeLeft = ("Left :\n" + std::to_string(time.count() - std::chrono::duration_cast<std::chrono::seconds>(now - begin).count()) + " seconds\nto kill all enemies");
	}
}

bool Timer::elapsed() noexcept {
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	return (time.count() <= std::chrono::duration_cast<std::chrono::seconds>(now - begin).count());
}

unsigned int Timer::getCountedTime() {
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	return abs(std::chrono::duration_cast<std::chrono::seconds>(now - begin).count());
}

void Timer::setBegin() {
	begin = std::chrono::steady_clock::now();
}

void Timer::stop() noexcept {
	if (!disabled) { // zabezpieczenie przed nieustanna zmiana wartosci pozostalego czasu
		disabled = true;
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		time -= std::chrono::duration_cast<std::chrono::seconds>(now - begin);
	}
}

void Timer::start() noexcept {
	if (disabled) { // zabezpieczenie przed nieustanna zmiana wartosci punktu poczatkowego
		setBegin();
		disabled = false;
	}
}

sf::String Timer::getTimeString() {
	return timeLeft;
}