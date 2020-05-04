#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include "Functions.h"
#include<SFML/Graphics.hpp>


#define FONT_PATH  "fonts/Schaeffer.ttf"
#define SCOREBOARD_PATH "scoreboard.txt"
#define WIDTH  1280//1920
#define HEIGHT  720//1080



class Menu
{
	std::vector<sf::Text>menu;
	std::vector<sf::Text> options;
	std::vector<std::tuple<sf::Text, unsigned int>> scores;
	//std::vector<sf::Text> scores;
	//std::vector<int> points;
	sf::Font font;
	int current;
	bool restart;
	bool game;
	bool exit;
public:
	Menu();
	bool restarted();
	void drawMenu(sf::RenderWindow& window);
	//void changeMenu(bool started, bool change);
	void drawInGameMenu(sf::RenderWindow& window);
	bool loadScoreboard();
	bool saveScoreboard();
	bool sortScores();
	void drawScoreboard(sf::RenderWindow& window);
	bool addToScores(sf::RenderWindow& window, unsigned int score);
	void gameRunning();
	void gameStarted();
	void drawOptions(sf::RenderWindow& window);
	bool moveUp(bool started);
	bool moveDown();
	sf::Font getFont();
	bool loadFont(const std::string& fontPath);
	bool handle(sf::RenderWindow& window, bool started);
	bool instruction(sf::RenderWindow& window);
	~Menu() = default;
};

