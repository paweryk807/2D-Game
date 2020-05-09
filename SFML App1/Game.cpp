#include "Game.h"

Game::Game(std::vector<std::string>& enemiesTextures, const std::string& playerT) : hud(100), player(playerT), spawner(std::chrono::seconds(45)) {
    try {
        sf::View view(sf::Vector2f(1280.0 / 2, 720.0 / 2), sf::Vector2f(1280, 720));
        view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
        //player = std::unique_ptr<Player>{ new Player(playerT) };
        level = std::unique_ptr<Map>{ new Map(3600,"level3.txt") };
        hud.setValue(player.getHealth());
        window = std::unique_ptr<sf::RenderWindow>{ new sf::RenderWindow(sf::VideoMode(1920, 1080), "The 2D-Game!", sf::Style::Fullscreen | sf::Style::Resize) };
        window->setKeyRepeatEnabled(false);
        window->setFramerateLimit(60);
        window->setView(view);
        started = false;
        pause = false;
    }
    catch (std::exception e) {
        std::cerr << e.what();
    }
}

bool Game::addBonus(Bird bonusBird)
{
    switch (bonusBird.getBonusType()) {
    case utils::BonusType::boost:
        player.setWalkSpeed(player.getSpeed() + bonusBird.receiveBonus()); // A BIT STATIC 
        break;
    case utils::BonusType::health:
        player.setHealth(player.getHealth() + bonusBird.receiveBonus());
        break;
    case utils::BonusType::strength:
        player.setStrength(player.getStrength() + bonusBird.receiveBonus());
        break;
    case utils::BonusType::time:
        spawner.setTime(std::chrono::seconds(spawner.getTimer().getCountedTime() + (int)bonusBird.receiveBonus()));
        break;
    default:
        return 0.0f;
    }
    return true;
}

void Game::soldierHanlder(bool& killed){
    sf::Vector2f direction;
    for (int i = 0; i < spawner.soldiers.size(); i++) {
        if (spawner.soldiers[i]->refresh(player, level->wall(spawner.soldiers[i].get()))) {
            if (level->checkPosition(spawner.soldiers[i].get())) {
                spawner.soldiers[i]->correctPosition(level->getSize());
            }
            /*   Czy gracz ma tarcze   */
            if (player.getShieldState()) {
                if (spawner.soldiers[i]->getHealth() > 0 && spawner.soldiers[i]->getCollider().checkCollision(player.getShieldCollider(), direction, 1.0f))
                    player.setHealth(player.getHealth() - 0.01);
                else if (spawner.soldiers[i]->getHealth() > 0 && spawner.soldiers[i]->getCollider().checkCollision(player.getCollider(), direction, 1.0f)) {
                    player.setHealth(player.getHealth() - 0.25);
                }
            }
            else if (spawner.soldiers[i]->getHealth() > 0 && spawner.soldiers[i]->getCollider().checkCollision(player.getCollider(), direction, 0.35f)) {
                player.setHealth(player.getHealth() - 0.5);
            }
            /*    Gracz zginal    */
            if (player.getHealth() <= 0 || spawner.getTimer().elapsed()) {
                spawner.getTimer().stop();
                gameOver();
                if (menu.addToScores(*window, score))
                    menu.saveScoreboard();
                pause = true;
                menu.handle(*window, false);
                break;
            }
            level->checkCollision(direction, spawner.soldiers[i].get());


        

            for (auto& elem : player.bullets) {
                if (!elem.getCooldown().elapsed() && elem.isUsed()) {
                    if (!level->checkBulletCollision(direction, &elem)) {
                        if (spawner.soldiers[i]->getHealth() > 0)
                            if (elem.hit(spawner.soldiers[i].get())) {
                                elem.hide();
                                spawner.soldiers[i]->setHealth(spawner.soldiers[i]->getHealth() - player.getStrength()); // metoda dekrementuj zdrowie(wartosc o ile)
                                if (spawner.soldiers[i]->getHealth() <= 0) {
                                    spawner.soldiers[i]->setStrength(0);
                                }
                            }
                    }
                    else elem.hide();
                }
            }


            



            /*
            if (!spawner.soldierBullets[0]->getCooldown().elapsed()) {
                if (!level->checkBulletCollision(direction, spawner.soldierBullets[0].get()))
                    if (spawner.soldiers[i]->getHealth() > 0)
                        if (spawner.soldierBullets[0]->hit(spawner.soldiers[i].get())) {
                            spawner.soldiers[i]->setHealth(spawner.soldiers[i]->getHealth() - player->getStrength()); // metoda dekrementuj zdrowie(wartosc o ile)
                            if (spawner.soldiers[i]->getHealth() <= 0) {
                                spawner.soldiers[i]->setStrength(0);
                            }
                        }
            }
            */






            
            /*      Sprawdzenie kolizji soldier'ow      */
            if (spawner.soldiers[i]->getHealth() > 0) { // jesli ten ktory sprawdza
                for (int n = i; n < spawner.soldiers.size(); n++) {
                    if (n != i) {
                        if (spawner.soldiers[n]->getHealth() > 0)  // jesli ktorys inny
                            if (spawner.soldiers[i]->getCollider().checkCollision(spawner.soldiers[n]->getCollider(), direction, 0.75f))
                                if (spawner.soldiers[i]->getPosition().y != spawner.soldiers[n]->getPosition().y && abs(spawner.soldiers[i]->getPosition().x - spawner.soldiers[n]->getPosition().x) < 40)
                                    spawner.soldiers[i]->setSpeed(0.5, sf::seconds(0.51));
                        level->checkCollision(direction, spawner.soldiers[n].get());// {

                    }
                }
            }
            //   level->checkCollision(direction, spawner.enemies[i]);// {

        }
        else {
            spawner.soldiers.erase(spawner.soldiers.begin() + i);
            player.addExp(20);
            score += 20;
        }

        if (spawner.soldiers.empty() && spawner.drones.empty())
            killed = true;
        //if (round == 1 || round == 2) {
        //    player->correctPosition(sf::Vector2f(0, 100));
        //    ptaszyskoTestowe.correctPosition(sf::Vector2f(0, 100));
        //    //dronik.correctPosition(sf::Vector2f(0, 100));
        //    generateLevel();
        // }
    }
}

void Game::dronesHanlder()
{
    sf::Vector2f direction;
    for (auto& elem : spawner.drones) {
        for(auto& bullet : player.bullets) {
            if (bullet.getCollider().checkCollision(elem.get()->getCollider(), direction, 1.0f)) {
                elem.get()->setHealth(elem.get()->getHealth() - player.getStrength());
                bullet.hide();
            }
        }
        elem.get()->refresh(&player, level->checkCollision(direction, elem.get()));
        if (elem.get()->getPosition() != sf::Vector2f(2000, 2000)) {
            window->draw(*elem.get());
        }

    }
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

void Game::restart() {
    spawner.soldiers.clear();
    spawner.soldierBullets.clear();
    std::chrono::seconds s = std::chrono::seconds(utils::randomInt(20, 25));
    spawner.setTime(s);
    score = 0;
    pause = false; 
	player.reset();	
    spawner.soldierBullets.push_back(std::unique_ptr<Bullet>(new Bullet(player.getPosition())));
    spawner.spawnSoldiers(5, 0);
    start();
}

void Game::run() {
    if (!menu.handle(*window, started)) {
       start();	
    }
}

void Game::generateLevel() {
    level.get_deleter(); 
    level = std::unique_ptr<Map>(new Map(3600, "level2.txt"));
    /*
        FUNKCJA DO ZMIANY PLANSZY 
        W.I.P

    */
     
}

void Game::start() {
    started = true;
    sf::Vector2f direction;
    sf::Image ss;
    sf::Texture sst;
    sst.create(window.get()->getSize().x, window.get()->getSize().y);
    round = 1;
    //generateLevel(); //             <------ Zrobic predefiniowane levele w switchu 
    Bird ptaszyskoTestowe(sf::Vector2f(400,450));
    bool shooted = false;
    bool killed = false;

    while (window->isOpen())
    {
        sf::Event event;
        if (!pause)
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
                        pause = (menu.handle(*window, started));
                    }
                    else {
                        pause = true;
                    }
                }
                if (event.key.code == sf::Keyboard::RShift) {

                    sst.update(*window);
                    ss = sst.copyToImage();
                    std::string filename = "screenshots/screenshot_" + std::to_string(utils::randomInt(1,700)) + std::to_string(utils::randomInt(99,1450)) + std::to_string(utils::randomInt(33,99)) + ".png";
                    ss.saveToFile(filename);
                }
                if (event.key.code == sf::Keyboard::O) {
                    player.setShieldState(!player.getShieldState());
                }
                break;
            }
        }
        window->clear();

        if(!window->hasFocus()) {
            spawner.getTimer().stop();
            pause = (menu.handle(*window, started));
        }
        /*   Jesli odpalona jest gra    */    
        if (!pause) {
            spawner.getTimer().start();
            getActionFromUser();
            soldierHanlder(killed);


            /*      Gracz trafil ptaka      */
            for(auto&elem : player.bullets)
                if(!elem.getCooldown().elapsed() && elem.isUsed())
                    if (elem.getCollider().checkCollision(ptaszyskoTestowe.getCollider(), direction, 1.0f)) {
                        elem.hide();
                        shooted = true;
                        addBonus(ptaszyskoTestowe);
                    }

            window->draw(*level);

            for (auto& elem : spawner.dronesBullets)
                for (auto& bullet : elem) {
                    bullet->refresh();
                    window->draw(*bullet);

                    if(bullet->hit(&player)) {
                        player.setHealth(player.getHealth() - 10);
                        if (player.getHealth() <= 0 || spawner.getTimer().elapsed()) {
                            spawner.getTimer().stop();
                            gameOver();
                            if (menu.addToScores(*window, score))
                                menu.saveScoreboard();
                            pause = true;
                            menu.handle(*window, false);
                            break;
                        }
                    }
                }


            if (killed) {
                spawner.soldiers.clear();
                std::chrono::seconds s;
                score += spawner.getTimer().getCountedTime() * 100;


                if (round < 2) {
                    spawner.spawnPlasmaDrone(10, round * 5);
                    s = std::chrono::seconds(utils::randomInt(4 * round + 20, 4 * round + 25));
                }
                else {
                    spawner.spawnSoldiers(round * 2 + 5, utils::randomInt(0, 3));
                    spawner.levelUpEnemies(round);
                    s = std::chrono::seconds(utils::randomInt(2 * round + 20, 2 * round + 25));
                }
                round++;


                spawner.getTimer().setTime(s);
                spawner.getTimer().start();
                if (utils::randomFloat(0, 100) < 25.f) {
                    shooted = false;
                    ptaszyskoTestowe.reset();
                }
                killed = false;
            }
            else if (!killed && spawner.drones.size() != 0) {
                // DRONY 
                dronesHanlder();
            }




            spawner.getTimer().refresher();
            hud.update(&player, &spawner.getTimer(), round, score);
            window->draw(hud);



            for (auto& elem : spawner.soldierBullets) {
                if (!elem->getCooldown().elapsed()) {
                    if (!level->checkBulletCollision(direction, elem.get())) {
                        if (elem != spawner.soldierBullets[0]) {
                            if (player.getShieldState()) {
                                if (elem->getCollider().onCollision(player.getShieldCollider())) {
                                    elem->hide();
                                }
                            }
                            if (elem->hit(&player)) {
                                player.setHealth(player.getHealth() - 1.5);
                            }
                        }
                        elem->refresh();
                        window->draw(*elem);
                    }
                }
            }
            for (auto& elem : spawner.soldiers) {
                window->draw(*elem);
            }
            window->draw(player);
            ptaszyskoTestowe.fly(level->checkCollision(direction, &ptaszyskoTestowe), shooted);
            window->draw(ptaszyskoTestowe);
        }

        if (menu.restarted()) {
            restart();
        }
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        player.shot();
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
        player.setSpeedToSprint();
    }
    else {
        player.setSpeedToWalk();
    }

    if (player.refresh())
        spawner.soldierBullets[0]->upgrade(player.getLevel());

    if (!level->checkPosition(&player)) {
        player.correctPosition(level->getSize());
    }
    level->checkCollision(sf::Vector2f(0, 0), &player);

}


Game::~Game() {
    spawner.soldierBullets.clear();
    spawner.soldiers.clear();
}  