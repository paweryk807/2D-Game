#pragma once
#include<string>
#include<iostream>
#include "Functions.h"
#include<SFML/Graphics.hpp>


#define FONT_PATH  "fonts/Schaeffer.ttf"
#define SCOREBOARD_PATH "scoreboard.txt"
#define WIDTH  1920
#define HEIGHT  1080



class Menu
{
	std::vector<sf::Text>menu;
	std::vector<sf::Text> options;
	sf::Font font;
	int current;
	bool restart;
public:
	Menu();
	bool restarted();
	void drawMenu(sf::RenderWindow& window);
	void changeMenu(bool started, bool change);
	void drawInGameMenu(sf::RenderWindow& window);
	void drawScoreboard(sf::RenderWindow& window);
	void gameRunning();
	void gameStarted();
	void drawOptions(sf::RenderWindow& window);
	bool moveUp(bool started);
	bool moveDown();
	sf::Font getFont();
	bool loadFont(const std::string& fontPath);
	bool handle(sf::RenderWindow& window, sf::View view, bool started);
	bool instruction(sf::RenderWindow& window);
	~Menu() = default;
};

