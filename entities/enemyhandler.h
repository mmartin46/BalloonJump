#ifndef ENEMY_HANDLER_H
#define ENEMY_HANDLER_H
#pragma once
#include <vector>
#include <random>
#include <memory>
#include "enemy.h"
#include "spike.h"

using std::vector;

constexpr int DISTANCE_BETWEEN_ENEMIES = 100;
constexpr int SPIKE_FREQUENCY = 6;

class EnemyHandler
{
    private:
        std::vector<std::shared_ptr<Enemy>> enemies;
        sf::RenderWindow *window_ptr;
        bool should_gen_general_enemy(int index);
    public:
        EnemyHandler() : update_functions{&update_enemies, &update_stomped_enemies} {}
        EnemyHandler(sf::RenderWindow *window) : window_ptr(window)
        {}
        // Allocates the needed number of enemies for the game
        vector<std::shared_ptr<Enemy>> allocate_enemies(const int NUM_ENEMIES, int min_x, int max_x, int min_y, int max_y);
        
        void update_stomped_enemies(Player *player); 
        // Updates all the enemies
        void update_enemies(Player *player) noexcept;
        // Draws all the enemies
        void draw_enemies() noexcept;

        vector<void (EnemyHandler::*)(Player*)> update_functions;

        // Returns a pointer to an enemy.
        std::shared_ptr<Enemy> get_enemy(int idx);
        vector<std::shared_ptr<Enemy>>* get_enemies() { return &enemies; };

        // Roomate Suggestion
        // FIXME: Add a Manhattan distance ( off-screen ) function between a player and enemy
        // When they aren't on the screen get rid of them.
};

#endif