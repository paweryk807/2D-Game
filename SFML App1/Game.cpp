#include "Game.h"



//   dodac pasek zycia postaci 
//   wyswietlac damage zadane postacia 


Game::Game(sf::View& view, std::vector<std::string>& enemiesTextures, const std::string& playerT) : view(view) {
    this->enemiesTextures = enemiesTextures;
    loadTexture(playerT);
    // loadEnemiesTextures(enemiesTextures); // Tymczasowo 0   DO TESTOW !!!!!!!!!!!!!!!
    level = std::unique_ptr<Level>{ new Level(sf::Vector2f(1920.f,1080.f), BACKGROUND_1)};
    player = new Player(playerTexture);
    window = std::unique_ptr<sf::RenderWindow>{ new sf::RenderWindow(sf::VideoMode(1920, 1080), "The 2D-Game!", sf::Style::Fullscreen | sf::Style::Resize) };
    window->setKeyRepeatEnabled(false);
    window->setFramerateLimit(60);
    view.setCenter(sf::Vector2f(1920.0 / 2, 1080.0 / 2)); //(player.getPosition());
    view.setSize(sf::Vector2f(1920.0, 1080.0));
    window->setView(view);
    started = false;
    pause = false;
    int round = 0;

}
bool Game::loadTexture(const std::string& texture) {
	if (!playerTexture.loadFromFile(texture)) {
		throw std::exception("unable to open texture file");
        return 0;
	}
    return 1;
}
void Game::restart() {
    enemiesToSpawn.clear();
    bullets.clear();
     pause = false; 
	 player->reset();
	 bullets.push_back(Bullet(player->getPosition()));
	enemiesToSpawn = addEnemies(5, 0);
     start();
}

void Game::run() {
    if (!menu.handle(*window.get(), view, started)) {
       start();	
    }
    
}

void Game::generateLevel() {
   	level->addPlatform(new Platform(SHEET, sf::Vector2f(19000.0f, 40.0f), sf::Vector2f(10.0f, 400.0f)));
    level->addPlatform(new Platform(SHEET, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(700.0f, 360.0f)));
    level->addPlatform(new Platform(SHEET, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(480.0f, 360.0f)));
    level->addPlatform(new Platform(SHEET, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(900.0f, 300.0f)));
    level->addPlatform(new Platform(SHEET, sf::Vector2f(140.0f, 40.0f), sf::Vector2f(1000.0f, 200.0f)));
}

std::vector<Soldier*> Game::addEnemies(const int enemiesToSpawn, const int type) {
    std::vector<Soldier*> toSpawn;
    std::vector<std::string> tmp;

    for (int i = 0; i < enemiesToSpawn; i++) {
           tmp.clear();
           //type
           int type = std::rand() % 4;
     switch (type) {
        case 0: //BLUE
            for (int a = 0; a < 4; a++) {
                tmp.push_back(enemiesTextures[a]);
            }
         break;        
        case 1: //RED
            for (int a = 4; a < 8; a++) {
                tmp.push_back(enemiesTextures[a]);
            }
            break;
        case 2: //YELLOW
            for (int a = 8; a < 12; a++) {
                tmp.push_back(enemiesTextures[a]);
            }
            break;
        case 3: //GREEN
            for (int a = 12; a < 16; a++) {
                tmp.push_back(enemiesTextures[a]);
            }
            break;
        default:
            throw std::exception("Bad enemy type");
            break;            
           
        } 
      toSpawn.push_back(new Soldier(tmp));
      toSpawn[i]->correctPosition(sf::Vector2f(toSpawn[i]->getPosition().x - i * 32, toSpawn[i]->getPosition().y));
    }       
    return toSpawn;

}

void Game::printRound(int number) {
    sf::Text object;
    std::string round = "Round";// + static_cast<char>(number);
    object.setString(round + " " + static_cast<char>(number+48));
    sf::Vector2f factors(1.f, 1.f);  
    sf::Font font;
    font.loadFromFile(FONT_PATH);
    object.setFont(font);
    object.setFillColor(sf::Color::Magenta);
    object.setScale(factors);
    object.setOutlineThickness(0.5f);
    object.setOutlineColor(sf::Color::White);
    object.setPosition(sf::Vector2f(WIDTH/2 - (round.length()+1.5f) *10, ((HEIGHT/2)/6))); // /6 dla symetrii
    window->draw(object);
}

void Game::start() {

    started = true;
    sf::Vector2f direction;


    int round = 1;
    generateLevel(); //             <------ Zrobic predefiniowane levele w switchu 


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
                        pause = (menu.handle(*window.get(), view, started));
                    }
                    else {
                        pause = true;
                    }
                }
                break;
            case sf::Event::Resized:
                ResizeView(*window.get(), view);
                break;
            }
        }
        window->clear();

        if(!window->hasFocus())
            pause = (menu.handle(*window.get(), view, started));

        if (!pause) {
            getActionFromUser();

            for (int i = 0; i < enemiesToSpawn.size(); i++) {
                if (level->checkPosition(enemiesToSpawn[i])) {
                    enemiesToSpawn[i]->correctPosition(level->getSize());
                    enemiesToSpawn[i]->refresh(*player, level->wall(enemiesToSpawn[i]));// bedzie trzeba je refreshowac jeszcze ... powinny biegac w strone gracza  

                }

                if (enemiesToSpawn[i]->getCollider().checkCollision(player->getCollider(), direction, 0.2f)) {
                    player->setHealth(player->getHealth() - 0.5);
                    if (player->getHealth() == 0) {
                        pause = true;
                        menu.handle(*window.get(), view, false);
                        break;
                    }
                }

                level->checkCollision(direction, enemiesToSpawn[i]);

                if (!bullets[0].getCooldown().elapsed()) {
                    if (!level->checkBulletCollision(direction, bullets[0]))
                        if (bullets[0].hit(enemiesToSpawn[i])) {
                            shot = false;
                            enemiesToSpawn[i]->setHealth(enemiesToSpawn[i]->getHealth() - player->getStrength());
                            if (enemiesToSpawn[i]->getHealth() <= 0) {
                                enemiesToSpawn.erase(enemiesToSpawn.begin() + i);
                            }
                        }
                }
                for (int n = i; n < enemiesToSpawn.size(); n++) {
                    if (n != i) {
                        enemiesToSpawn[i]->getCollider().checkCollision(enemiesToSpawn[n]->getCollider(), direction, 0.1f);
                    }
                }

                if (enemiesToSpawn.empty()) {
                    round++;
                    enemiesToSpawn.clear();
                    enemiesToSpawn = addEnemies(round * 2 + 5, 0);
                }

            }

            level->draw(*window.get());
            printRound(round);

            for (int z = 0; z < enemiesToSpawn.size(); z++) {
                window->draw(enemiesToSpawn[z]->getSprite());
            }

            window->draw(player->getSprite());

            if (shot) {
                if (!bullets[0].getCooldown().elapsed())
                    if (!level->checkBulletCollision(direction, bullets[0])) {
                        window->draw(bullets[0].getSprite());
                        bullets[0].refresh();
                    }
                    else shot = false;
            }
        }

        if (menu.restarted()) {
            restart();
        }

        window->display();
    }
}


void Game::getActionFromUser() {

    if (player->getCanClimb()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player->moveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player->moveDown();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        if (bullets[0].getCooldown().elapsed()) {
            shot = true; 
            bullets[0].restart(player->getPosition() );
            bullets[0].setDirection(player);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->moveLeft();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->moveRight();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player->jump();

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        player->setSpeed(6.65, sf::seconds(0.075));
    }
    else {
        player->setSpeed(4.20, sf::seconds(0.125));
    }

    player->refresh();
  
    if (!level->checkPosition(player)) {
        player->correctPosition(level->getSize());
    }
    level->checkCollision(sf::Vector2f(0,0) , player);
      
}


bool Game::loadEnemiesTextures(std::vector<std::string>& textures)
{
    for (int i = 0; i < textures.size(); i++) {
        sf::Texture texture;
        if (!texture.loadFromFile(textures[i].data())) {
            throw std::exception("unable to open texture file");
            return 0;
        }
    }
    return 1;
}

Game::~Game() {
    //for (auto elem : enemiesToSpawn) {
     //   delete elem;
    //}
}  