#pragma once
#include "map.h"
#include "entities/player.h"

#include <SFML/Graphics.hpp>
#include "map.h"
#include "entities/player.h"
#include "background.h"
#include <memory>
#include "enemyhandler.h"
#include "header.h"

#define PLAYER_INIT_X 100
#define PLAYER_INIT_Y 100

constexpr int MAX_ENEMY_X = 5000;
constexpr int MAX_ENEMY_Y = -2000;
constexpr int ENEMY_COUNT = 30;

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

void Game::enemy_collision_handler()
{
    int x, y, z;
    for (x = 0; x < game_map->get_rows(); ++x)
    {
        for (y = 0; y < game_map->get_columns(); ++y)
        {
            for (auto &enemy : *enemy_handler.get_enemies())
            {
                entity_collision(*enemy, x, y, {ENEMY_WIDTH, ENEMY_HEIGHT});            
            }
        }
    }    
}

Game::Game(sf::RenderWindow *window, Map *map) : window(window), game_map(map), player(PLAYER_INIT_X, PLAYER_INIT_Y), header(window)
{
    background = std::make_shared<Background>("1330857.jpg", *window);
    enemy_handler = EnemyHandler(window);

    header.set_string("Player");

    enemy_handler.allocate_enemies(ENEMY_COUNT, 1000, MAX_ENEMY_X, -3000, MAX_ENEMY_Y);
    game_view.setSize(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

bool Game::player_landed_on_enemy(Player &plyr, std::pair<int, int> dim)
{
    int touched = 0;
    Matrix<Tile> &tiles = *game_map->get_tile_map();
    float pw = dim.first, ph = dim.second;
    float px = plyr.get_x(), py = plyr.get_y();

    for (auto &enemy : *enemy_handler.get_enemies())
    {
        float ex = enemy->get_x();
        float ey = enemy->get_y();
        float ew = ENEMY_WIDTH;
        float eh = ENEMY_HEIGHT;

        if (px + pw > ex && px < ex + ew && py + ph > ey && py < ey)
        {
            enemy->set_stomped_on(true);
            return true;
        }

    }
    return false;

}


int Game::entity_collision(Player &plyr, int i, int j, std::pair<int, int> dim)
{
    int touched = 0;
    Matrix<Tile> &tiles = *game_map->get_tile_map();
    float pw = dim.first, ph = dim.second;
    float px = plyr.get_x(), py = plyr.get_y();
    float bx = tiles.at(i).at(j).get_x(), by = tiles.at(i).at(j).get_y();
    float bw = TILE_SIZE, bh = TILE_SIZE;

    if ((tiles.at(i).at(j).get_value() == 0) || (tiles.at(i).at(j).get_value() == 5))
    {
        return 0;
    }

    // Allow the enemy to move through coins
    Enemy *enemy = dynamic_cast<Enemy*>(&plyr);
    if (enemy && (tiles.at(i).at(j).get_value() == 5))
    {
        return 0;
    }

    if (px+pw/2 > bx && px+pw/2 < bx+bw)
    {
        // Head Bump
        if (py < by+bh && py>by && plyr.get_dy() < 0)
        {
            // correct y
            plyr.set_y((by+bh) + 1);
            py = by+bh;

            // bumped our head, stop any jump velocity
            //plyr.set_dy(0);
            plyr.set_on_ground(false);
            plyr.set_is_jumping(true);
            touched = 1;
        }
    }
    if (px+pw > bx && px<bx+bw)
    {
        // Head bump
        if (py+ph > by && py < by && plyr.get_dy() > 0)
        {
            // correct y
            plyr.set_y(by-ph);
            py = by-ph;

            //landed on this ledge, stop any jump velocity
            plyr.set_dy(0);
            plyr.set_on_ground(true);
            //plyr.set_is_jumping(false);
            touched = 2;
        }
    }

    if (py+ph > by && py<by+bh)
    {
        // Rubbing against right edge
        if (px < bx+bw && px+pw > bx+bw && plyr.get_dx() < 0)
        {
            // correct x
            plyr.set_x(bx+bw);
            px = bx+bw;

            plyr.set_dx(0);
            touched = 3;
        }
        // Rubbing against left edge
        else if (px+pw > bx && px < bx && plyr.get_dx() > 0)
        {
            // correct x
            plyr.set_x(bx-pw);
            px = bx-pw;

            plyr.set_dx(0);
            touched = 4;
        }
    }
    return touched;

}

bool Game::check_tile_collision(const sf::Sprite &sprite, const sf::Sprite &tile_sprite)
{
    sf::FloatRect sprite_bounds = sprite.getGlobalBounds();
    sf::FloatRect tile_bounds = tile_sprite.getGlobalBounds();

    return sprite_bounds.intersects(tile_bounds);
}


void Game::collision_handler()
{
    player.set_on_ground(false);
    int x, y;
    for (x = 0; x < game_map->get_rows(); ++x)
    {
        for (y = 0; y < game_map->get_columns(); ++y)
        {
            Tile *current_tile = &game_map->get_tile_map()->at(x).at(y);
            if (check_tile_collision(player.get_sprite(), *current_tile->get_sprite()))
            {
                // Check for a coin
                if (current_tile->get_value() == 5)
                {
                    game_map->get_tile_map()->at(x).at(y).set_value(0);
                }
                player.set_on_ground(true);
            }


            entity_collision(player, x, y, {PLAYER_WIDTH, PLAYER_HEIGHT});
        }
    }
}



void Game::draw()
{

    background->draw();
    game_map->draw();

    player.draw(*window);
    enemy_handler.draw_enemies();
    header.draw();

    window->setView(game_view);
    //window->setView(window->getDefaultView());
}

void Game::update()
{
    player.update();
    enemy_handler.update_enemies(&player);
    collision_handler();
    enemy_collision_handler();

    static float background_dy;

    background_dy = player.get_dy();
    if (background_dy >= 1)
    {
        background_dy = 1;
    }
    else if (background_dy <= -1)
    {
        background_dy = -1;
    }


    background->scroll(player.get_dx(),(int) background_dy);
    header.scroll(player.get_dx() , background_dy);
    // Testing
    if (player_landed_on_enemy(player, {PLAYER_WIDTH, PLAYER_HEIGHT}))
    {
        player.set_dy(JUMP_HEIGHT / 2);
    }


    game_view.setCenter(get_player().get_x() + PLAYER_WIDTH / 2, get_player().get_y() + PLAYER_HEIGHT / 2);
}
