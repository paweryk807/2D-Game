#include "Game.h"

Game::Game(std::vector<std::string>& enemiesTextures, const std::string& playerT) : hud(100), spawner(std::chrono::seconds(45)) {
    try {
        sf::View view(sf::Vector2f(1280.0 / 2, 720.0 / 2), sf::Vector2f(1280, 720));
        view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
        player = std::unique_ptr<Player>{ new Player(playerT) };
        level = std::unique_ptr<Map>{ new Map(3600,"level.txt") };
        hud.setValue(player->getHealth());
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
        player->setSpeed(player->getSpeed() + bonusBird.receiveBonus(), sf::seconds(3.f)); // A BIT STATIC 
        break;
    case utils::BonusType::health:
        player->setHealth(player->getHealth() + bonusBird.receiveBonus());
        break;
    case utils::BonusType::strength:
        player->setStrength(player->getStrength() + bonusBird.receiveBonus());
        break;
    case utils::BonusType::time:
        spawner.setTime(std::chrono::seconds(spawner.getTimer().getCountedTime() + (int)bonusBird.receiveBonus()));
        break;
    default:
        return 0.0f;
    }
    return true;
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
	player->reset();	
    spawner.soldierBullets.push_back(new Bullet(player->getPosition()));
    spawner.spawnSoldiers(5, 0);
    start();
}

void Game::run() {
    if (!menu.handle(*window, started)) {
       start();	
    }
}

void Game::generateLevel() {
    level->changeMap("level2.txt", 3600);
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
    std::vector<PlasmaBullet*> bullets;
    PlasmaBullet* tmp = nullptr;
    for (int i = 0; i < 25; i++) {
        tmp = new PlasmaBullet(sf::Vector2f(120, 120), 2.f+0.5f*i);//, texture[0]);
    //	tmp->setIntRect(sf::IntRect(0, 0, 64, 64));
        bullets.push_back(tmp);
    }
    PlasmaDrone dronik(bullets);
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
                    player->setShieldState(!player->getShieldState());
                }
                break;
            }
        }
        window->clear();

        if (!window->hasFocus()) {
            spawner.getTimer().stop();
            pause = (menu.handle(*window, started));
        }
        /*   Jesli odpalona jest gra    */    
        if (!pause) {
            spawner.getTimer().start();
            getActionFromUser();
            for (int i = 0; i < spawner.soldiers.size(); i++) {
                if (spawner.soldiers[i]->refresh(*player, level->wall(spawner.soldiers[i]))) {
                    if (level->checkPosition(spawner.soldiers[i])) {
                        spawner.soldiers[i]->correctPosition(level->getSize());
                    }
                    /*   Czy gracz ma tarcze   */
                    if (player->getShieldState()) {
                        if (spawner.soldiers[i]->getHealth() > 0 && spawner.soldiers[i]->getCollider().checkCollision(player->getShieldCollider(), direction, 1.0f))
                            player->setHealth(player->getHealth() - 0.01);
                        else if (spawner.soldiers[i]->getHealth() > 0 && spawner.soldiers[i]->getCollider().checkCollision(player->getCollider(), direction, 1.0f)) {
                            player->setHealth(player->getHealth() - 0.25);
                        }
                    }
                    else if (spawner.soldiers[i]->getHealth() > 0 && spawner.soldiers[i]->getCollider().checkCollision(player->getCollider(), direction, 0.35f)) {
                        player->setHealth(player->getHealth() - 0.5);
                    }
                    /*    Gracz zginal    */
                    if (player->getHealth() <= 0 || spawner.getTimer().elapsed()) {
                        spawner.getTimer().stop();
                        gameOver();
                        if (menu.addToScores(*window, score))
                            menu.saveScoreboard();
                        pause = true;
                        menu.handle(*window, false);
                        break;
                    }
                    level->checkCollision(direction, spawner.soldiers[i]);

                    /*      Gracz trafil ptaka      */
                    if (!spawner.soldierBullets[0]->getCooldown().elapsed()) {
                        // DODAC ZMIENNA BOOL DO INFORMOWANIA CZY JEST BOSS NIECH TO BEDZIE W SPAWNERZE 
                        if (spawner.soldierBullets[0]->getCollider().checkCollision(dronik.getCollider(), direction, 1.0f)) {
                            dronik.setHealth(dronik.getHealth() - player->getStrength());
                        }
                        if (spawner.soldierBullets[0]->getCollider().checkCollision(ptaszyskoTestowe.getCollider(), direction, 1.0f)) {
                            shooted = true;
                            addBonus(ptaszyskoTestowe);
                        }
                        if (!level->checkBulletCollision(direction, *spawner.soldierBullets[0]))
                            if (spawner.soldiers[i]->getHealth() > 0)
                                if (spawner.soldierBullets[0]->hit(spawner.soldiers[i])) {
                                    spawner.soldiers[i]->setHealth(spawner.soldiers[i]->getHealth() - player->getStrength()); // metoda dekrementuj zdrowie(wartosc o ile)
                                    if (spawner.soldiers[i]->getHealth() <= 0) {
                                        spawner.soldiers[i]->setStrength(0);
                                    }
                                }
                    }
                    /*      Sprawdzenie kolizji soldier'ow      */
                    if (spawner.soldiers[i]->getHealth() > 0) { // jesli ten ktory sprawdza
                        for (int n = i; n < spawner.soldiers.size(); n++) {
                            if (n != i) {
                                if (spawner.soldiers[n]->getHealth() > 0)  // jesli ktorys inny
                                    if (spawner.soldiers[i]->getCollider().checkCollision(spawner.soldiers[n]->getCollider(), direction, 0.75f))
                                        if (spawner.soldiers[i]->getPosition().y != spawner.soldiers[n]->getPosition().y && abs(spawner.soldiers[i]->getPosition().x - spawner.soldiers[n]->getPosition().x) < 40)
                                            spawner.soldiers[i]->setSpeed(0.5, sf::seconds(0.51));
                                level->checkCollision(direction, spawner.soldiers[n]);// {

                            }
                        }
                    }
                 //   level->checkCollision(direction, spawner.enemies[i]);// {

                }
                else {
                    spawner.soldiers.erase(spawner.soldiers.begin() + i);
                    player->addExp(20);
                    score += 20;
                }

                if (spawner.soldiers.empty()) {
                    if (round == 1) {
                        player->correctPosition(sf::Vector2f(0, 100));
                        ptaszyskoTestowe.correctPosition(sf::Vector2f(0, 100));
                        dronik.correctPosition(sf::Vector2f(0, 100));
                        generateLevel();
                    }
                    round++;
                    score += spawner.getTimer().getCountedTime() * 100;
                    spawner.soldiers.clear();
                    Bullet* tmp = spawner.soldierBullets[0];
                    spawner.soldierBullets.clear();
                    spawner.soldierBullets.push_back(tmp);
                    spawner.spawnSoldiers(round * 2 + 5, utils::randomInt(0, 3));
                    spawner.levelUpEnemies(round);
                    std::chrono::seconds s = std::chrono::seconds(utils::randomInt(2 * round + 20, 2 * round + 25));
                    spawner.getTimer().setTime(s);
                    spawner.getTimer().start();
                    if (utils::randomFloat(0, 100) < 25.f) {
                        shooted = false;
                        ptaszyskoTestowe.reset();
                    }

                }
            }
      

            
            
            spawner.getTimer().refresher();
            hud.update(player.get(), &spawner.getTimer(), round, score);
            window->draw(*level);
            window->draw(hud);
            dronik.refresh(player.get(), level->checkCollision(direction, &dronik));
            if (dronik.getPosition() != sf::Vector2f(2000, 2000))
            window->draw(dronik);
            for (auto& elem : bullets) {
                elem->refresh();
                if (!elem->getCooldown().elapsed())
                    window->draw(*elem);
            }

            for (auto& elem : spawner.soldierBullets) {
                if (!elem->getCooldown().elapsed()) {
                    if (!level->checkBulletCollision(direction, *elem)) {
                        if (elem != spawner.soldierBullets[0]) {
                            if (player->getShieldState()) {
                                if (elem->getCollider().onCollision(player->getShieldCollider())) {
                                    elem->hide();
                                }
                            }
                            if (elem->hit(player.get())) {
                                player->setHealth(player->getHealth() - 1.5);
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
            window->draw(*player);
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

    if (player->getCanClimb()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player->moveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player->moveDown();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        if (spawner.soldierBullets[0]->getCooldown().elapsed()) {
            spawner.soldierBullets[0]->restart(player->getPosition() );
            spawner.soldierBullets[0]->setDirection(player.get());
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
        spawner.soldierBullets[0]->upgrade(player->getLevel());
 
    if (!level->checkPosition(player.get())) {
        player->correctPosition(level->getSize());
    }
    level->checkCollision(sf::Vector2f(0,0) , player.get());
      
}

Game::~Game() {
    spawner.soldierBullets.clear();
    spawner.soldiers.clear();
}  