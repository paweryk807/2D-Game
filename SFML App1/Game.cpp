#include "Game.h"

Game::Game(sf::View& view, std::vector<std::string>& enemiesTextures, const std::string& playerT) : view(view), hud(100), spawner(std::chrono::seconds(45)) {
    loadTexture(playerT);
    level = std::unique_ptr<Map>{ new Map(3600,"level.txt") };
    player = new Player(playerTexture);
    hud.setValue(player->getHealth());
    window = std::unique_ptr<sf::RenderWindow>{ new sf::RenderWindow(sf::VideoMode(1920, 1080), "The 2D-Game!", sf::Style::Fullscreen | sf::Style::Resize) };
    window->setKeyRepeatEnabled(false);
    window->setFramerateLimit(60);
    //view.setCenter(sf::Vector2f(120.0 / 2, 1080.0 / 2));
   // view.setSize(sf::Vector2f(1920.0, 1080.0));
    window->setView(view);
    started = false;
    pause = false;

}

void Game::gameOver()
{
    std::chrono::seconds showTime(3);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    sf::Text text;
    text.setString("Game Over");
    text.setCharacterSize(35);
    int size = ((text.getString().getSize())/2 - 1) * (35 + text.getLetterSpacing());
    text.setPosition(WIDTH / 2 - size, HEIGHT / 2);
    sf::Font f;
    f.loadFromFile(FONT_PATH);
    text.setFont(f);
    window->clear();
    window->draw(text);
    window->display();
    do {
        now = std::chrono::steady_clock::now();
    } while (showTime.count() >= abs(std::chrono::duration_cast<std::chrono::seconds>(begin - now).count()));

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
    pause = false; 
	player->reset();	
    spawner.bullets.push_back(new Bullet(player->getPosition()));
    spawner.spawnEnemies(5, 0);
    start();
}

void Game::run() {
    if (!menu.handle(*window, view, started)) {
       start();	
    }
}

void Game::generateLevel() {
    /*
        FUNKCJA DO ZMIANY PLANSZY 
        W.I.P

    */
}

void Game::start() {
    /* GENERATOR LICZB LOSOWYCH */
 
    /*--------------------------*/

    started = true;
    sf::Vector2f direction;

    sf::Image ss;
    sf::Texture sst;
    sst.create(window.get()->getSize().x, window.get()->getSize().y);
    int number = 0;
    round = 1;
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
                    spawner.getTimer().stop();
                    if (!pause) {
                        pause = (menu.handle(*window, view, started));
                    }
                    else {
                        pause = true;
                    }
                }
                if (event.key.code == sf::Keyboard::RShift) {

                    sst.update(*window);
                    ss = sst.copyToImage();
                    std::string filename = "screenshots/screenshot_" + std::to_string(utils::randomInt(1,7)) + std::to_string(utils::randomInt(99,1450)) + std::to_string(utils::randomInt(33,99)) + "_" + std::to_string(number) + ".png";
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

        if (!window->hasFocus()) {
            spawner.getTimer().stop();
            pause = (menu.handle(*window, view, started));
        }

        if (!pause) {
            spawner.getTimer().start();
            getActionFromUser();
            for (int i = 0; i < spawner.enemies.size(); i++) {
                if (spawner.enemies[i]->refresh(*player, level->wall(spawner.enemies[i]))) {
                    if (level->checkPosition(spawner.enemies[i])) {
                        spawner.enemies[i]->correctPosition(level->getSize());
                    }

                    if (player->getShieldState()) {
                        if (spawner.enemies[i]->getHealth() > 0 && spawner.enemies[i]->getCollider().checkCollision(player->getShieldCollider(), direction, 1.0f))
                            player->setHealth(player->getHealth() - 0.01);
                        else if (spawner.enemies[i]->getHealth() > 0 && spawner.enemies[i]->getCollider().checkCollision(player->getCollider(), direction, 1.0f)) {
                            player->setHealth(player->getHealth() - 0.25);
                        }
                    }
                    else if (spawner.enemies[i]->getHealth() > 0 && spawner.enemies[i]->getCollider().checkCollision(player->getCollider(), direction, 0.35f)) {
                        player->setHealth(player->getHealth() - 0.5);
                    }
                    if (player->getHealth() <= 0 || spawner.getTimer().elapsed()) {
                        gameOver();
                        spawner.getTimer().stop();
                        if (menu.addToScores(*window, score))
                            menu.saveScoreboard();
                        pause = true;
                        menu.handle(*window, view, false);
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
                                    if (spawner.enemies[i]->getCollider().checkCollision(spawner.enemies[n]->getCollider(), direction, 1.0f))
                                        if (spawner.enemies[i]->getPosition().y != spawner.enemies[n]->getPosition().y && abs(spawner.enemies[i]->getPosition().x - spawner.enemies[n]->getPosition().x) < 40)
                                            spawner.enemies[i]->setSpeed(0.5, sf::seconds(0.51));
                            }
                        }
                    }
                }
                else {
                    spawner.enemies.erase(spawner.enemies.begin() + i);
                    player->addExp(20);
                    score += 20;
                }

                if (spawner.enemies.empty()) {
                    round++;
                    score += spawner.getTimer().getCountedTime() * 100;
                    spawner.enemies.clear();
                    Bullet* tmp = spawner.bullets[0];
                    spawner.bullets.clear();
                    spawner.bullets.push_back(tmp);
                    spawner.spawnEnemies(round * 2 + 5, utils::randomInt(0,3));
                    std::chrono::seconds s = std::chrono::seconds(utils::randomInt(2 * round  + 20, 2*round + 25));
                    spawner.getTimer().setTime(s);
                    spawner.getTimer().start();
        
                }
            }
            spawner.getTimer().refresher();
            hud.update(player, &spawner.getTimer(), round, score);
            window->draw(*level);
            window->draw(hud);


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
                        window->draw(*elem);
                    }
                }
            }
            for (auto& elem : spawner.enemies) {
                window->draw(*elem);
            }
            window->draw(*player);
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
 
    if (!level->checkPosition(player)) {
        player->correctPosition(level->getSize());
    }
    level->checkCollision(sf::Vector2f(0,0) , player);
      
}

Game::~Game() {
    delete player;
    spawner.bullets.clear();
    spawner.enemies.clear();
}  