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
	/*
	Klasa odpowiedzialna za menu gry 
	*/
	std::vector<sf::Text>menu;
	std::vector<sf::Text> options;
	std::vector<std::tuple<sf::Text, unsigned int>> scores;
	sf::Font font;
	int current; // parametr sluzy jako wskaznik elementu na ktorym w menu znajduje sie uzytkownik 
	bool restart;
	bool game;
	bool exit;
public:
	Menu();

	bool restarted();
	/* Wyswietlanie menu, gdy nie uzytkownik nie jest w trakcie gry */
	void drawMenu(sf::RenderWindow& window);
	/* Wyswietlanie menu, gdy gra jest zastopowana */
	void drawInGameMenu(sf::RenderWindow& window);
	/* Wczytywanie tablicy wynikow z pliku */
	bool loadScoreboard();
	/* Zapis tablicy wynikow do pliku */
	bool saveScoreboard();
	/* Sortowanie wynikow */
	bool sortScores();
	/* Rysowanie tablciy wynikow na ekranie */
	void drawScoreboard(sf::RenderWindow& window);
	/* Dodawanie wyniku do tablicy */
	bool addToScores(sf::RenderWindow& window, unsigned int score);
	/* Opcje sa jeszcze niezaimplementowane. W przyszlosci maja byc one odpowiedzialna za zmiane wygladu postaci gracza
	oraz zmiane wyswietlanego tla. Mozliwe ze ustawiany bedzie w nich tez poziom trudnosci gry (zmiany czasowe, statystyki postaci)  */
	void drawOptions(sf::RenderWindow& window);
	/* Poruszanie sie po menu */
	bool moveUp(bool started);
	bool moveDown();
	
	sf::Font getFont();
	
	bool loadFont(const std::string& fontPath);
	/* Glowna metoda odpowiedzialna za obsluge menu gry */
	bool handle(sf::RenderWindow& window, bool started);
	/* Przechodzenie do innych zakladek menu, obsluga zdarzen */
	bool instruction(sf::RenderWindow& window);
	
	~Menu() = default;
};
