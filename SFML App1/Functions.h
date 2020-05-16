#pragma once
#include <SFML/Graphics.hpp>
/* Funkcja bedzie sprawdzala czy w otoczeniu gracza znajduje sie obiekt pozwalajacy na wspinanie sie
   ewentualnie zostanie ona przerobiona na metode klasy mapy */
bool isLadder(sf::Vector2f vct);
/* Funkcja utrzymujaca skale wyswietlanego obrazu w proporcjach takich jak zaprojektowany rozmiar przekazywany jako parametr */
sf::View calcView(const sf::Vector2u& windowsize, const sf::Vector2u& designedsize);
