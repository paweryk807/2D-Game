#include "Game.h"

Game::Game(sf::View& view, std::vector<std::string>& enemiesTextures, const std::string& playerT) : view(view), healthBar(100), spawner(std::chrono::seconds(45)) {
  //  this->enemiesTextures = enemiesTextures;
    loadTexture(playerT);
   // level = std::unique_ptr<Level>{ new Level(sf::Vector2f(1920.f,1080.f), BACKGROUND_1) };
    level = std::unique_ptr<Map>{ new Map(3600,"level.txt") };
    player = new Player(playerTexture);
    healthBar.setValue(player->getHealth());
    window = std::unique_ptr<sf::RenderWindow>{ new sf::RenderWindow(sf::VideoMode(1920, 1080), "The 2D-Game!", sf::Style::Fullscreen | sf::Style::Resize) };
    window->setKeyRepeatEnabled(false);
    window->setFramerateLimit(60);
    //view.setCenter(sf::Vector2f(120.0 / 2, 1080.0 / 2));
   // view.setSize(sf::Vector2f(1920.0, 1080.0));
    window->setView(view);
    started = false;
    pause = false;
    int round = 0;
    font.loadFromFile(FONT_PATH);
    object.setFont(font);
    object.setFillColor(sf::Color::Magenta);
    object.setScale(1.f,1.f);
    object.setOutlineThickness(0.5f);
    object.setOutlineColor(sf::Color::White);
}

bool Game::loadTexture(const std::string& texture) {
	if (!playerTexture.loadFromFile(texture)) {
		throw std::exception("unable to open texture file");
        return 0;
	}
    return 1;
}

void Game::restart() {
    spawner.enemies.clear();
    spawner.bullets.clear();
   // enemiesToSpawn.clear();   
   //  bullets.clear();
    //bullets.clear();
    pause = false; 
	player->reset();	
    spawner.bullets.push_back(new Bullet(player->getPosition()));
    //bullets.push_back(new Bullet(player->getPosition()));
  //  enemiesToSpawn = addEnemies(5);
    spawner.spawnEnemies(5, 0);
    start();
}

void Game::run() {
    if (!menu.handle(window.get(), view, started)) {
       start();	
    }
}

void Game::generateLevel() {
    /*
        FUNKCJA DO ZMIANY PLANSZY 
        W.I.P

    */
}
/*
std::vector<Soldier*> Game::addEnemies(const int enemiesToSpawn) {
    std::vector<Soldier*> toSpawn;
    std::vector<std::string> tmp;
    bullets.reserve(enemiesToSpawn);
    for (int i = 0; i < enemiesToSpawn; i++) {
           tmp.clear();
           /*  RANDOM TYPE SET  */
/*
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
      toSpawn[i]->correctPosition(sf::Vector2f(120 + rand() % 3,570 + rand() % 5));  //toSpawn[i]->getPosition().x - i * 2, toSpawn[i]->getPosition().y)
      bullets.push_back(new Bullet(toSpawn[i]->getPosition(), 11.f));
      toSpawn[i]->addAmmunition(*bullets[bullets.size()-1]);
    }       
    return toSpawn;

}
*/
void Game::printRound(int number) {
    std::string round = "Round : ";// + static_cast<char>(number);
    round += std::to_string(number);
    object.setString(round);
    object.setPosition(sf::Vector2f(WIDTH/2 - (round.length()+1.5f) *10, ((HEIGHT/2)/6))); // /6 dla symetrii
    window->draw(object);
}

void Game::start() {
    //level->reset();
    started = true;
    sf::Vector2f direction;

    sf::Image ss;
    sf::Texture sst;
    sst.create(window.get()->getSize().x, window.get()->getSize().y);
    int number = 0;
   // std::vector<Soldier*> enemiesToSpawn = std::move(spawner.enemies);
    //std::vector<Bullet*> bullets = std::move(spawner.bullets);

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
                        pause = (menu.handle(window.get(), view, started));
                    }
                    else {
                        pause = true;
                    }
                }
                if (event.key.code == sf::Keyboard::RShift) {

                    sst.update(*window);
                    ss = sst.copyToImage();
                    std::string filename = "screenshots/screenshot_" + std::to_string(number) + ".png";
                    ss.saveToFile(filename);
                    number++;
                }
                if (event.key.code == sf::Keyboard::O) {
                    player->setShieldState(!player->getShieldState());
                }
                break;
             case sf::Event::Resized:
                ResizeView(*window.get(), view);
                break;
            }
        }
        window->clear();

        if(!window->hasFocus())
            pause = (menu.handle(window.get(), view, started));

        if (!pause) {
            getActionFromUser();
            for (int i = 0; i < spawner.enemies.size(); i++) {
                if (spawner.enemies[i]->refresh(*player, level->wall(spawner.enemies[i]))) {
                  //  if (level->checkPosition(enemiesToSpawn[i])) {
                    //    enemiesToSpawn[i]->correctPosition(level->getSize());
                  //  }

                    if (player->getShieldState()) {
                        if (spawner.enemies[i]->getHealth() > 0 && spawner.enemies[i]->getCollider().checkCollision(player->getShieldCollider(), direction, 1.0f))
                            player->setHealth(player->getHealth() - 0.01);
                        else if (spawner.enemies[i]->getHealth() > 0 && spawner.enemies[i]->getCollider().checkCollision(player->getCollider(), direction, 1.0f)) {
                            player->setHealth(player->getHealth() - 0.25);
                        }
                    }
                    else if (spawner.enemies[i]->getHealth() > 0 && spawner.enemies[i]->getCollider().checkCollision(player->getCollider(), direction, 0.5f)) {
                        player->setHealth(player->getHealth() - 0.5);
                    }
                    if (player->getHealth() <= 0 || spawner.getTimer().elapsed()) {
                        pause = true;
                        menu.handle(window.get(), view, false);
                        break;
                    }
                    level->checkCollision(direction, spawner.enemies[i]);
                    /*        SEKCJA DO DODANIA POCISKOW ZOLNIERZY      */
                    if (!spawner.bullets[0]->getCooldown().elapsed()) {
                        if (!level->checkBulletCollision(direction, *spawner.bullets[0]))
                            if (spawner.bullets[0]->hit(spawner.enemies[i])) {
                                spawner.enemies[i]->setHealth(spawner.enemies[i]->getHealth() - player->getStrength()); // metoda dekrementuj zdrowie(wartosc o ile)
                                if (spawner.enemies[i]->getHealth() <= 0) {
                                    spawner.enemies[i]->setStrength(0);
                                    spawner.enemies[i]->setAtackSpeed(0);
                                }
                            }
                    }
                    if (spawner.enemies[i]->getHealth() > 0) { // jesli ten ktory sprawdza
                        for (int n = i; n < spawner.enemies.size(); n++) {
                            if (n != i) {
                                if (spawner.enemies[n]->getHealth() > 0)  // jesli ktorys inny
                                    spawner.enemies[i]->getCollider().checkCollision(spawner.enemies[n]->getCollider(), direction, 1.0f);
                            }
                        }
                    }
                }
                else {
                    spawner.enemies.erase(spawner.enemies.begin() + i);
                    player->addExp(20);
                }

                if (spawner.enemies.empty()) {
                    round++;
                    spawner.enemies.clear();
                    Bullet* tmp = spawner.bullets[0];
                    spawner.bullets.clear();
                    spawner.bullets.push_back(tmp);
                    spawner.spawnEnemies(round * 2 + 5, rand() % 3);
                    
                     // enemiesToSpawn = addEnemies(round * 2 + 5);
                }
            }

            spawner.getTimer().refresher();
         
            level->draw(*window.get());
            printRound(round);   
            spawner.getTimer().drawTimer(window.get());

            for(auto &elem : spawner.enemies) {
                window->draw(elem->getSprite());
            }

            if (player->getShieldState()) 
                window->draw(player->getShield());
            window->draw(player->getSprite());
            healthBar.draw(window.get());

            for (auto& elem : spawner.bullets) {
                if (!elem->getCooldown().elapsed()) {
                    if (!level->checkBulletCollision(direction, *elem)) {
                        if (elem != spawner.bullets[0]) {
                            if (player->getShieldState()) {
                                if (elem->getCollider().onCollision(player->getShieldCollider())) {
                                    elem->hide();
                                }
                            }
                            if (elem->hit(player)) {
                                player->setHealth(player->getHealth() - 1.5);
                            }
                        }
                        elem->refresh();
                        window->draw(elem->getSprite());
                    }
                }
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
        if (spawner.bullets[0]->getCooldown().elapsed()) {
            spawner.bullets[0]->restart(player->getPosition() );
            spawner.bullets[0]->setDirection(player);
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

    if (player->refresh())
        spawner.bullets[0]->upgrade(player->getLevel());

    healthBar.update(player);
  
    if (!level->checkPosition(player)) {
        player->correctPosition(level->getSize());
    }
    level->checkCollision(sf::Vector2f(0,0) , player);
      
}

/*
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
*/
Game::~Game() {
 //   enemiesToSpawn.clear(); 
 //   bullets.clear();
    spawner.bullets.clear();
    spawner.enemies.clear();
}  