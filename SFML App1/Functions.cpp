#include "Functions.h"

bool isLadder(sf::Vector2f vct){
	return 0; // uzaleznic to cudo od wspolrzednych x,y 
}

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = float((window.getSize().x) / float(window.getSize().y));
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}