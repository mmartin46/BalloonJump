#include "enemyhandler.h"

void EnemyHandler::update_stomped_enemies(Player *player)
{
    static std::random_device rand_dev;
    static std::mt19937 engine(rand_dev());
    std::uniform_int_distribution<int> rand_x_offset(900, 1500);
    std::uniform_int_distribution<int> rand_y_offset(0, 400);
    
    int x_off = rand_x_offset(engine);
    int y_off = rand_y_offset(engine);


    auto it = get_enemies()->begin();
    for (; it != get_enemies()->end(); ++it)
    {
        if ((*it)->get_stomped_on())
        {
            (*it)->set_x(player->get_x() + x_off);
            (*it)->set_y(player->get_y() - y_off);
            (*it)->set_stomped_on(false);
            break;
        }
    }
}

std::shared_ptr<Enemy> EnemyHandler::get_enemy(int idx)
{
    if (idx >= enemies.size() || idx < 0)
    {
        std::cout << "Enemy() -> get_enemy(idx) -> Index out of range" << std::endl;
        exit(1);
    }
    return enemies.at(idx);
}

vector<std::shared_ptr<Enemy>> EnemyHandler::allocate_enemies(const int NUM_ENEMIES, int min_x, int max_x, int min_y, int max_y)
{
    static std::random_device rand_dev;
    static std::default_random_engine engine(rand_dev());
    std::uniform_int_distribution<int> rand_x_pos(min_x, max_x + DISTANCE_BETWEEN_ENEMIES);
    std::uniform_int_distribution<int> rand_y_pos(min_y, max_y + DISTANCE_BETWEEN_ENEMIES);

    for (int i = 0; i < NUM_ENEMIES; ++i)
    {
        int x_pos = rand_x_pos(engine);
        int y_pos = rand_y_pos(engine);

        std::cout << x_pos << std::endl;

        enemies.push_back(std::make_shared<Enemy>(x_pos, y_pos));
    }
    return enemies;
}

void EnemyHandler::draw_enemies() noexcept
{
    typename vector<std::shared_ptr<Enemy>>::pointer enemy, enemy_end = enemies.data() + enemies.size();
    for (enemy = enemies.data(); enemy < enemy_end; ++enemy)
    {
        (*enemy)->draw(*window_ptr);
    }
}

void EnemyHandler::update_enemies(Player *player) noexcept
{
    typename vector<std::shared_ptr<Enemy>>::pointer enemy, enemy_end = enemies.data() + enemies.size();
    for (enemy = enemies.data(); enemy < enemy_end; ++enemy)
    {
        (*enemy)->update();
    }
    update_stomped_enemies(player);
}