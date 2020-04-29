#include "Timer.h"
Timer::Timer(std::chrono::seconds seconds) {
    time = seconds;
    begin = std::chrono::steady_clock::now();
    font.loadFromFile(TIME_FONT_PATH);
    timeLeft.setFont(font);
    timeLeft.setPosition(130, 620);
    timeLeft.setFillColor(sf::Color::Magenta);
    sf::Vector2f factors(0.75, 0.75);
    timeLeft.setScale(factors);
    timeLeft.setOutlineThickness(0.15f);
    timeLeft.setOutlineColor(sf::Color::Black);
    timeLeft.setString("Left :\n" + std::to_string(time.count()) + " seconds\nto kill all enemies");
    disabled = false;
}

void Timer::setTime(std::chrono::seconds seconds) noexcept {
    time = seconds;
}

void Timer::refresher() noexcept {
    if(!disabled){
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	timeLeft.setString("Left :\n" + std::to_string(time.count() - std::chrono::duration_cast<std::chrono::seconds>(now - begin).count()) + " seconds\nto kill all enemies");
    }
}

void Timer::drawTimer(sf::RenderWindow* window) const noexcept
{
	window->draw(timeLeft);
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