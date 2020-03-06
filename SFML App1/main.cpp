
#include <time.h>
#include <iostream>
#include "Player.h"
#include "Functions.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 512.0f;

const int H = 400; 
const int W = 400;
void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = float((window.getSize().x) / float(window.getSize().y));
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 512), "The Game!", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("images/characters.png")) {
        std::cout<<"Niepopranie zaladowane textury"<<std::endl;
    }

    sf::Texture platformTexture;
    if (!platformTexture.loadFromFile("images/sheet.png")) {
        std::cout<<"Niepopranie zaladowane textury"<<std::endl;
    }

    Player player(playerTexture);
    std::vector<Platform> platforms;
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(600.0f, 400.0f)));
	platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(700.0f, 360.0f)));
	platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(480.0f, 360.0f)));
	platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(900.0f, 300.0f)));
	platforms.push_back(Platform(&platformTexture, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(1000.0f, 200.0f)));
    
    bool esc = false;
    while (window.isOpen())
    {
        sf::Event event;
		
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }
        window.clear();
        view.setCenter(player.getPosition());
        window.setView(view);

        if (climb)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                player.moveUp();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                player.moveDown();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.moveLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.moveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            player.jump();
 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            player.setSpeed(2.65, sf::seconds(0.075));
        }
        else {
            player.setSpeed(2.20, sf::seconds(0.125));
        }
        player.refresh();

        sf::Vector2f direction;

        for (Platform& platform : platforms) {
            if (platform.getCollider().checkCollision(player.getCollider(),direction, 1.0f)) {
                player.onCollision(direction);
            }
        }

        for (Platform& platform : platforms) {
            platform.draw(window);
        }

        window.draw(player.getSprite());
        window.display();
    }

    return 0;
}
