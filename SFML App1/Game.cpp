#include "Game.h"
#include <stdexcept>

Game::Game(sf::View& view, const std::string& playerTexture, const std::string& platformTexture) : view(view) {
    loadPlatformTexture(platformTexture);
    loadPlayerTexture(playerTexture);
    level = std::unique_ptr<Level>{ new Level(sf::Vector2i(1920,1080),this->platformTexture) };
    player = Player(this->playerTexture);
    window = std::unique_ptr<sf::RenderWindow>{ new sf::RenderWindow(sf::VideoMode(1024, 512), "The 2D-Game!", sf::Style::Close | sf::Style::Resize) };
    window->setKeyRepeatEnabled(false);
    window->setFramerateLimit(60);
}

void Game::start() {
    bool esc = false;
    while (window->isOpen())
    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::Resized:
                ResizeView(*window.get(), view);
                break;
            }
        }
        window->clear();
        view.setCenter(player.getPosition());
        window->setView(view);

        if (player.canClimb) {
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
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
        if (!level->checkPosition(player)) {
            player.correctPosition(level->getSize());
        }
        level->checkCollision(direction, player);  
        level->draw(*window.get());
        window->draw(player.getSprite());
        window->display();
    }
}
bool Game::loadPlatformTexture(const std::string texture)
{
	if (!platformTexture.loadFromFile(texture)) {
		throw std::exception("unable to open texture file");
        return 0;
    }
	return 1;
}

bool Game::loadPlayerTexture(const std::string texture)
{
	if (!playerTexture.loadFromFile(texture)) {
		throw std::exception("unable to open texture file");
		return 0;
	}
	return 1;	
}

Game::~Game() {
}  