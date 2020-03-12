#pragma once
#include<string>
#include<iostream>
#include<SFML/Graphics.hpp>
#include"Settings.h"
#define FONT_PATH  "fonts/Schaeffer.ttf"
#define WIDTH  1920
#define HEIGHT  1080
#define NUMBER_OF_ITEMS 4 // game->characterSelect  options->difficult->hard/normal/easy  scoreboard 

class Menu
{
	sf::Text text[NUMBER_OF_ITEMS]; // 
	sf::Font font;
	int current;
public:
	Menu();
	void draw(sf::RenderWindow*window);
	bool moveUp();
	bool moveDown();
	bool loadFont(const std::string& fontPath);
	bool handle(sf::RenderWindow* window);
	~Menu() = default;
};

