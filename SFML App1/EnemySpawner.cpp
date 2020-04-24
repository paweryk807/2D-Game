#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(std::chrono::minutes minutes) {
	time = minutes;
}

bool const EnemySpawner::elapsed() noexcept
{
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	return (time.count() <= std::chrono::duration_cast<std::chrono::minutes>(now - begin).count());
}


void EnemySpawner::spawnEnemies(int value, int type)
{
    std::vector<Soldier*> toSpawn;
    std::vector<std::string> tmp;
    bullets.reserve(value);
    for (int i = 0; i < value; i++) {
        tmp.clear();
        /*  RANDOM TYPE SET  */
        //int type = std::rand() % 4;
        switch (type) {
        case 0: //BLUE
            tmp = std::move(TYPE_0);
            break;
        case 1: //RED
            tmp = std::move(TYPE_1);
            break;
        case 2: //YELLOW
            tmp = std::move(TYPE_2);
            break;
        case 3: //GREEN
            tmp = std::move(TYPE_3);
            break;
        default:
            throw std::exception("Bad enemy type param.");
            break;
        }
        toSpawn.push_back(new Soldier(tmp));
        toSpawn[i]->correctPosition(sf::Vector2f(120 + rand() % 3, 570 + rand() % 5));  //toSpawn[i]->getPosition().x - i * 2, toSpawn[i]->getPosition().y)
        bullets.push_back(new Bullet(toSpawn[i]->getPosition(), 11.f));
        toSpawn[i]->addAmmunition(*bullets[bullets.size() - 1]);
    }
}

