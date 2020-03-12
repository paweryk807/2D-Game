#include "Game.h"


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
    bool pause = false;


    //BACKGROUND APLHA 
    sf::RectangleShape background;
    sf::Texture backText;
    backText.loadFromFile("images/background.jpg");
    sf::Vector2f s(1920, 1080);
    background.setSize(s);
    background.setTexture(&backText);
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
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Escape) {
                    if (!pause) {
                        pause = true;
                        showMenu();
                    }
                    else {
                        pause = false;
                        hideMenu();
                    }
                }
                break;
            case sf::Event::Resized:
                ResizeView(*window.get(), view);
                break;
            }
        }
        window->clear(); 
     
        view.setCenter(sf::Vector2f(1920.0 / 2, 1080.0 / 2)); //(player.getPosition());
        view.setSize(sf::Vector2f(1920.0, 1080.0));
        window->setView(view);

        //BACKGROUND ALPHA 
        window->draw(background);
        if (!pause)
        {
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


        }
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

bool Game::showMenu() {
    Menu menu;
   // window->clear();
    menu.handle(window.get());
    return 1;
}
bool Game::hideMenu() {
    return 0;
}

Game::~Game() {
}  