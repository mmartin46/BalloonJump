#ifndef ENEMY_HANDLER_H
#define ENEMY_HANDLER_H
#pragma once
#include <vector>
#include <random>
#include <memory>
#include "enemy.h"

using std::vector;

constexpr int DISTANCE_BETWEEN_ENEMIES = 100;

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
        vector<std::shared_ptr<Enemy>> allocate_enemies(const int NUM_ENEMIES, int min_x, int max_x, int min_y, int max_y);
        
        void update_stomped_enemies(Player *player); 
        // Updates all the enemies
        void update_enemies(Player *player) noexcept;
        // Draws all the enemies
        void draw_enemies() noexcept;

        // Returns a pointer to an enemy.
        std::shared_ptr<Enemy> get_enemy(int idx);
        vector<std::shared_ptr<Enemy>>* get_enemies() { return &enemies; };
};

#endif