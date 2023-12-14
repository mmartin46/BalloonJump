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
constexpr int MIN_ENEMY_X = 1000;
constexpr int MIN_ENEMY_Y = -3000;
constexpr int PLAYER_COIN_LIMIT = 10;
constexpr int COIN_VALUE = 5;

using std::to_string;
using std::pair;

#define WORLD_MAP(stage, level)  world::world_maps.at(stage).at(level)


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
        bool game_over;
        bool level_complete;
        pair<int, int> current_level;

        void init_current_level();
    public:
        Game(sf::RenderWindow *window, Map *game_map);
        Player get_player() { return player; }

        void draw();
        void update();
        int entity_collision(Player &plyr, int i, int j, std::pair<int, int> dim);
        void collision_handler();
        bool check_tile_collision(const sf::Sprite &sprite, const sf::Sprite &tile_sprite);
        void enemy_collision_handler();
        bool player_landed_on_enemy(Player &plyr, const std::pair<int, int> &dim); 
        void set_game_over(bool state) { game_over = state; }
        bool is_game_over() { return game_over; }
        void handle_game_over();

        void player_reset_position(Player &player);
        void player_reset_assets(Player &player);

        void player_enemy_collision_handling();
        void change_game_map();
};


#endif