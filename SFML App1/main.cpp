
#include <time.h>
#include <iostream>
#include "Player.h"
#include "Functions.h"
#include "Platform.h"
#include "Game.h"




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
	//sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    	sf::View view(sf::Vector2f(1920.0/2, 1080.0/2), sf::Vector2f(1920, 1080));
    std::unique_ptr<Game> giera;//{ new Level(sf::Vector2i(1920,1080),this->platformTexture) };
    try {
        giera = std::unique_ptr<Game>{ new Game(view, "images/characters.png", "images/sheet.png") };
        giera->start();
    }
    catch (std::exception & e) {
        std::cerr << "Cos poszlo nie tak ;(\n";
    }

    return 0;
}
