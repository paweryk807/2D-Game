#include "Game.h"

//   cooldown do strzelania 
//   ogarnac podazanie  -------- moze za poprzednia pozycja a nie za aktualna (byloby oporowo plynniej)
//   skakanie postaci tylko wtedy gdy poprzednia jej poprzednia pozycja jest taka sama jak aktualna ( w sensie ze moze sie o cos zablokowala 
//   dodac pasek zycia postaci 
//   wyswietlac damage zadane postacia 
//   
//


Game::Game(sf::View& view, std::vector<std::string>& enemiesTextures, const std::string& playerTexture, const std::string& platformTexture) : view(view) {
    loadPlatformTexture(platformTexture); // MOZE ZWROCIC NIMI WARTOSC SF::TEXTURE  ------- MNIEJ KODU 
    loadPlayerTexture(playerTexture);
    loadEnemiesTextures(enemiesTextures, 0); // Tymczasowo 0   DO TESTOW !!!!!!!!!!!!!!!
    level = std::unique_ptr<Level>{ new Level(sf::Vector2i(1920,1080),this->platformTexture) };
    player = Player(this->playerTexture);
    window = std::unique_ptr<sf::RenderWindow>{ new sf::RenderWindow(sf::VideoMode(1920, 1080), "The 2D-Game!", sf::Style::Fullscreen | sf::Style::Resize) };
    window->setKeyRepeatEnabled(false);
    window->setFramerateLimit(60);
    view.setCenter(sf::Vector2f(1920.0 / 2, 1080.0 / 2)); //(player.getPosition());
    view.setSize(sf::Vector2f(1920.0, 1080.0));
    window->setView(view);
    started = false;
    pause = false;
       
}

void Game::restart() {
    player = Player(playerTexture);
    enemiesToSpawn.clear();
    enemiesToSpawn = addEnemies(50, 0); // Test jednego dziada 
    started = true;
    pause = false;
    // RESET WORLD 
}

void Game::run() {
    if (menu.handle(*window.get(), view, started)) {
        start();
    }
}

std::vector<Enemy> Game::addEnemies(const int enemiesToSpawn, const int type) {
    std::vector<Enemy> toSpawn;
    for (int i = 0; i < enemiesToSpawn; i++) {
        switch (type) {
        case 0:
            toSpawn.push_back(enemiesTypes[0]);
            toSpawn[i].correctPosition(sf::Vector2i(toSpawn[i].getPosition().x - i * 32, toSpawn[i].getPosition().y));
            break;        
        case 1:
            toSpawn.push_back(enemiesTypes[1]);
            break;        
        case 2:
            toSpawn.push_back(enemiesTypes[2]);
            break;        
        case 3:
            toSpawn.push_back(enemiesTypes[3]);
            break;
        case 4:
            toSpawn.push_back(enemiesTypes[4]);
            break;
        default:
            throw std::exception("Bad enemy type");
            break;
        }
    }       
    return toSpawn;

}


void Game::start() {

    started = true;
    enemiesToSpawn = addEnemies(50, 0); // Test jednego dziada 

    //BACKGROUND APLHA 
    sf::RectangleShape background;
    sf::Texture backText;
    backText.loadFromFile("images/background.jpg");
    sf::Vector2f s(1920, 1080);
    background.setSize(s);
    background.setTexture(&backText);
    //
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
                        pause = !(menu.handle(*window.get(), view, started));
                    }
                    else {
                        pause = false;
                    }

                }
                break;
            case sf::Event::Resized:
                ResizeView(*window.get(), view);
                break;
            }
        }
        window->clear();

        //BACKGROUND ALPHA 
        window->draw(background);
        sf::Vector2f direction;

        if (!pause) { 
            getActionFromUser();
            for (int i = 0; i < enemiesToSpawn.size(); i++) {
                if (!level->checkPosition(&enemiesToSpawn[i])) {
                     enemiesToSpawn[i].correctPosition(level->getSize());  
                     enemiesToSpawn[i].refresh(player, false);// bedzie trzeba je refreshowac jeszcze ... powinny biegac w strone gracza 
                }
                else {
                    enemiesToSpawn[i].refresh(player, true);// bedzie trzeba je refreshowac jeszcze ... powinny biegac w strone gracza 
                }
                if (enemiesToSpawn[i].getCollider().checkCollision(player.getCollider(), direction, 0.2f)) {
                    player.setHealth(player.getHealth() - 0.5);
                    if (player.getHealth() == 0) {
                        pause = true;
                        menu.handle(*window.get(), view, false);
                        break;
                    }
                }
                for (int n = i; n < enemiesToSpawn.size(); n++) {
                    if (n != i) {
                       enemiesToSpawn[i].getCollider().checkCollision(enemiesToSpawn[n].getCollider(), direction, 0.1f);
                    }
                }
               level->checkCollision(direction, & enemiesToSpawn[i]);
            }
        }
        if (menu.restarted()) {
            restart();
        }
        level->draw(*window.get());
        for (auto elem : enemiesToSpawn) {
            window->draw(elem.getSprite());
        }
        window->draw(player.getSprite());
        window->display();
    }
}

void Game::getActionFromUser() {
    if (player.getCanClimb()) {
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
    if (!level->checkPosition(&player)) {
        player.correctPosition(level->getSize());
    }
    level->checkCollision(direction, &player);
      
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

bool Game::loadEnemiesTextures(std::vector<std::string>& textures, const int type)
{
    for (int i = 0; i < textures.size(); i++) {
        sf::Texture texture;
        if (!texture.loadFromFile(textures[type].data())){
            throw std::exception("unable to open texture file");
            return 0;
        }
        enemiesTypes.push_back(playerTexture);//Enemy(texture));
    }
    return 1;
}

Game::~Game() {
}  