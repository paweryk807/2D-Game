#pragma once
#include <SFML/Graphics.hpp>

static const float VIEW_HEIGHT = 512.0f;


bool isLadder(sf::Vector2f vct);

void ResizeView(const sf::RenderWindow& window, sf::View& view);
