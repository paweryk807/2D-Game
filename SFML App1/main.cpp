
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
//#include "Player.h"
//#include "Functions.h"
//#include "Platform.h"
#include "Game.h"
#include  "TileMap.h"
#include "vld.h"
//using namespace std;



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

std::unique_ptr<Game> giera;//{ new Level(sf::Vector2i(1920,1080),this->platformTexture) };

    std::vector<std::string> enemies;

    enemies.push_back("images/Blue/Gunner_Blue_Idle.png");
    enemies.push_back("images/Blue/Gunner_Blue_Run.png");
    enemies.push_back("images/Blue/Gunner_Blue_Jump.png");
    enemies.push_back("images/Blue/Gunner_Blue_Death.png");

    enemies.push_back("images/Red/Gunner_Red_Idle.png");
    enemies.push_back("images/Red/Gunner_Red_Run.png");
    enemies.push_back("images/Red/Gunner_Red_Jump.png");
    enemies.push_back("images/Red/Gunner_Red_Death.png");

    enemies.push_back("images/Yellow/Gunner_Yellow_Idle.png");
    enemies.push_back("images/Yellow/Gunner_Yellow_Run.png");
    enemies.push_back("images/Yellow/Gunner_Yellow_Jump.png");
    enemies.push_back("images/Yellow/Gunner_Yellow_Death.png");

    enemies.push_back("images/Green/Gunner_Green_Idle.png");
    enemies.push_back("images/Green/Gunner_Green_Run.png");
    enemies.push_back("images/Green/Gunner_Green_Jump.png");
    enemies.push_back("images/Green/Gunner_Green_Death.png");

    try {
        giera = std::unique_ptr<Game>{ new Game(enemies, "images/characters.png") };
        giera->run();
    }
    catch (std::exception & e) {
        std::cerr << "Cos poszlo nie tak ;(\n";
    }
    


    return 0;
}
