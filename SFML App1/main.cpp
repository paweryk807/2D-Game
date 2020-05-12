#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"
#include  "TileMap.h"
//#include "vld.h"

/*
Ograniczenie czasowe na bossow i jak nie wyrobimy sie w konkretnym czasie to np tracimy zycie

ukrycie konsoli

instalator

zmienna szybkosc gry (postaci)
randomizacja
el. zaskoczenia
timer

rozrysowac diagram klas
draw.io

*/

int main()
{
	//sf::RectangleShape sprite;
//sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
//sf::View view(sf::Vector2f(1280.0/2, 720.0/2), sf::Vector2f(1280, 720));

 //sf::RenderWindow window(sf::VideoMode(1280, 720), "Tilemap");

//view.setCenter(view.getSize().x / 2, view.getSize().y /  2);

	std::unique_ptr<Game> giera;
	try {
		giera = std::unique_ptr<Game>{ new Game() };
		giera->run();
	}
	catch (std::exception& e) {
		std::cerr << "Cos poszlo nie tak ;(\n";
	}

	return 0;
}