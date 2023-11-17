#pragma once
#include <vector>
#include <random>
#include <memory>
#include "enemy.h"

using std::vector;

class EnemyHandler
{
    private:
        std::vector<std::shared_ptr<Enemy>> enemies;
        sf::RenderWindow *window_ptr;
    public:
        EnemyHandler() {}
        EnemyHandler(sf::RenderWindow *window) : window_ptr(window)
        {}
        // Allocates the needed number of enemies for the game
        vector<std::shared_ptr<Enemy>> allocate_enemies(const int NUM_ENEMIES, int x_boundary, int y_boundary);
        
        void update_stomped_enemies(Player *player); 
        // Updates all the enemies
        void update_enemies(Player *player);
        // Draws all the enemies
        void draw_enemies();

        // Returns a pointer to an enemy.
        std::shared_ptr<Enemy> get_enemy(int idx);
        vector<std::shared_ptr<Enemy>>* get_enemies() { return &enemies; };
};

void EnemyHandler::update_stomped_enemies(Player *player)
{
    std::random_device rand_dev;
    std::default_random_engine engine(rand_dev());
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

vector<std::shared_ptr<Enemy>> EnemyHandler::allocate_enemies(const int NUM_ENEMIES, int x_boundary, int y_boundary)
{
    std::random_device rand_dev;
    std::default_random_engine engine(rand_dev());
    std::uniform_int_distribution<int> rand_x_pos(100, x_boundary);
    std::uniform_int_distribution<int> rand_y_pos(-100, y_boundary);

    for (int i = 0; i < NUM_ENEMIES; ++i)
    {
        int x_pos = rand_x_pos(engine);
        int y_pos = rand_y_pos(engine);

        enemies.push_back(std::make_shared<Enemy>(x_pos, y_pos));
    }
    return enemies;
}

void EnemyHandler::draw_enemies()
{
    typename vector<std::shared_ptr<Enemy>>::pointer enemy, enemy_end = enemies.data() + enemies.size();
    for (enemy = enemies.data(); enemy < enemy_end; ++enemy)
    {
        (*enemy)->draw(*window_ptr);
    }
}

void EnemyHandler::update_enemies(Player *player)
{
    typename vector<std::shared_ptr<Enemy>>::pointer enemy, enemy_end = enemies.data() + enemies.size();
    for (enemy = enemies.data(); enemy < enemy_end; ++enemy)
    {
        (*enemy)->update();
    }
    update_stomped_enemies(player);
}
