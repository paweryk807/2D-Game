#include "EnemySpawner.h"




EnemySpawner::EnemySpawner() : EnemySpawner(std::chrono::seconds(10)) {}
EnemySpawner::EnemySpawner(std::chrono::seconds seconds) : timer(seconds) {}

Timer& EnemySpawner::getTimer()
{
    return timer;
}

void EnemySpawner::setTime(std::chrono::seconds seconds) {
    timer.setTime(seconds);
}

void EnemySpawner::spawnEnemies(int value, int type)
{
    timer.start();
    enemies.clear();
    enemies.reserve(value);
    std::vector<std::string> tmp;
    bullets.reserve(value);
    for (int i = 0; i < value; i++) {
        tmp.clear();
        /*  RANDOM TYPE SET  */
        //int type = std::rand() % 4;
        switch (type) {
        case 0: //BLUE
            tmp = { "images/Blue/Gunner_Blue_Idle.png", "images/Blue/Gunner_Blue_Run.png", "images/Blue/Gunner_Blue_Jump.png", "images/Blue/Gunner_Blue_Death.png" };
            break;
        case 1: //RED
            tmp = { "images/Red/Gunner_Red_Idle.png", "images/Red/Gunner_Red_Run.png", "images/Red/Gunner_Red_Jump.png", "images/Red/Gunner_Red_Death.png" };
            break;
        case 2: //YELLOW
            tmp = { "images/Yellow/Gunner_Yellow_Idle.png", "images/Yellow/Gunner_Yellow_Run.png", "images/Yellow/Gunner_Yellow_Jump.png", "images/Yellow/Gunner_Yellow_Death.png" };
            break;
        case 3: //GREEN
            tmp = { "images/Green/Gunner_Green_Idle.png", "images/Green/Gunner_Green_Run.png", "images/Green/Gunner_Green_Jump.png", "images/Green/Gunner_Green_Death.png" };
            break;
        default:
            throw std::exception("Bad enemy type param.");
            break;
        }
        enemies.push_back(new Soldier(tmp));
        enemies[i]->correctPosition(sf::Vector2f(120 + rand() % 3, 570 + rand() % 5));  //toSpawn[i]->getPosition().x - i * 2, toSpawn[i]->getPosition().y)
        bullets.push_back(new Bullet(enemies[i]->getPosition(), 11.f));
        enemies[i]->addAmmunition(*bullets[bullets.size() - 1]);
    }
    //enemies.push_back(new PlasmaDrone());
}

void EnemySpawner::levelUpEnemies(int round) {
    for (auto& elem : enemies) {
        elem->levelUp(round);
    }
}



