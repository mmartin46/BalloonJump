#ifndef GAME_H
#define GAME_H
#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "../utils/map.h"
#include "../entities/player.h"
#include "../utils/background.h"
#include <memory>
#include "../entities/enemyhandler.h"
#include "../utils/header.h"

#define PLAYER_INIT_X 100
#define PLAYER_INIT_Y 100

constexpr int MAX_ENEMY_X = 5000;
constexpr int MAX_ENEMY_Y = -2000;
constexpr int ENEMY_COUNT = 30;

using std::to_string;

class Game
{
    private:
        sf::RenderWindow *window;
        sf::View game_view;
        
        Map *game_map;
        std::shared_ptr<Background> background;

        GameHeader header;
        EnemyHandler enemy_handler;
        Player player;
        int coins_collected = 0;
        int enemies_destroyed = 0;
    public:
        Game(sf::RenderWindow *window, Map *game_map);
        Player get_player() { return player; }

        void draw();
        void update();
        int entity_collision(Player &plyr, int i, int j, std::pair<int, int> dim);
        void collision_handler();
        bool check_tile_collision(const sf::Sprite &sprite, const sf::Sprite &tile_sprite);
        void enemy_collision_handler();

        bool player_landed_on_enemy(Player &plyr, std::pair<int, int> dim);        
};

#endif