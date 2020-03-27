#include "Game.h"



//   dodac pasek zycia postaci 
//   wyswietlac damage zadane postacia 


Game::Game(sf::View& view, std::vector<std::string>& enemiesTextures, const std::string& playerT, const std::string& platformTexture) : view(view) {
    loadPlatformTexture(platformTexture); // MOZE ZWROCIC NIMI WARTOSC SF::TEXTURE  ------- MNIEJ KODU 
    loadTexture(playerT);
    loadEnemiesTextures(enemiesTextures, 0); // Tymczasowo 0   DO TESTOW !!!!!!!!!!!!!!!
    level = std::unique_ptr<Level>{ new Level(sf::Vector2i(1920,1080),this->platformTexture) };
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
  //  start();
  //  player->reset();
   // enemiesToSpawn = addEnemies(5, 0);

    // RESET WORLD 
}

void Game::run() {
    if (!menu.handle(*window.get(), view, started)) {
       start();	
    }
    
}

std::vector<Enemy*> Game::addEnemies(const int enemiesToSpawn, const int type) {
    std::vector<Enemy*> toSpawn;
    for (int i = 0; i < enemiesToSpawn; i++) {
        switch (type) {
        case 0:
            toSpawn.push_back(new Enemy(playerTexture));
            toSpawn[i]->correctPosition(sf::Vector2i(toSpawn[i]->getPosition().x - i * 32, toSpawn[i]->getPosition().y));
            break;        
        case 1:
           // toSpawn.push_back(enemiesTypes[1]);
            break;        
        case 2:
           // toSpawn.push_back(enemiesTypes[2]);
            break;        
        case 3:
           // toSpawn.push_back(enemiesTypes[3]);
            break;
        case 4:
           // toSpawn.push_back(enemiesTypes[4]);
            break;
        default:
            throw std::exception("Bad enemy type");
            break;
        }
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


	int round = 1;       


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
                        pause =  (menu.handle(*window.get(), view, started));
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
        //BACKGROUND ALPHA 
        window->draw(background);   
        printRound(round);

        sf::Vector2f direction;
        
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
                    if (bullets[0].hit(enemiesToSpawn[i])) {
                        shot = false;
                            enemiesToSpawn[i]->setHealth(enemiesToSpawn[i]->getHealth() - player->getStrength());
                            if (enemiesToSpawn[i]->getHealth() <= 0) {
                                std::cout << "zabil" << std::endl;
                                enemiesToSpawn.erase(enemiesToSpawn.begin() + i);
                                   
                                /*if (i != (enemiesToSpawn.size() - 1 && enemiesToSpawn.size() != 1)) {
                                    delete enemiesToSpawn[i];
                                    enemiesToSpawn[i] = enemiesToSpawn[enemiesToSpawn.size() - 1];
                                    // enemiesToSpawn[enemiesToSpawn.size() - 1] = nullptr;
                                    //  delete tmp;
                                }
                                 

                                //enemiesToSpawn.pop_back();*/

                        }
                    } 
                }
                for (int n = i; n < enemiesToSpawn.size(); n++) {
                    if (n != i) {
                        enemiesToSpawn[i]->getCollider().checkCollision(enemiesToSpawn[n]->getCollider(), direction, 0.1f);
                    }
                } 

                
            if (enemiesToSpawn.empty()) {
                std::cout << "KONIEC RUNDY"<<std::endl;
                round++;
                enemiesToSpawn.clear();
                enemiesToSpawn = addEnemies(round * 2 + 5, 0);
            } 

            } 
            level->draw(*window.get());
            for(int z = 0; z < enemiesToSpawn.size(); z++) {
                window->draw(enemiesToSpawn[z]->getSprite());
            }
            window->draw(player->getSprite());
            if (shot) {
                if (!bullets[0].getCooldown().elapsed()) {
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
        player->setSpeed(2.65, sf::seconds(0.075));
    }
    else {
        player->setSpeed(2.20, sf::seconds(0.125));
    }
    player->refresh();
  
    sf::Vector2f direction;
    if (!level->checkPosition(player)) {
        player->correctPosition(level->getSize());
    }
    level->checkCollision(direction, player);
      
}
bool Game::loadPlatformTexture(const std::string texture)
{
	if (!platformTexture.loadFromFile(texture)) {
		throw std::exception("unable to open texture file");
        return 0;
    }
	return 1;
}


bool Game::loadEnemiesTextures(std::vector<std::string>& textures, const int type)
{
    //for (int i = 0; i < textures.size(); i++) {
       // sf::Texture texture;
       // if (!texture.loadFromFile(textures[type].data())){
          //  throw std::exception("unable to open texture file");
        //    return 0;
      //  }
  //     enemiesTypes.push_back(new Enemy(playerTexture));//Enemy(texture));
    //}
    return 1;
}

Game::~Game() {
    //for (auto elem : enemiesToSpawn) {
     //   delete elem;
    //}
}  