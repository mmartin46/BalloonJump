#include "game.h"

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
            plyr.set_y(by+bh);
            py = by+bh;

            // bumped our head, stop any jump velocity
            plyr.set_dy(0);
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

    if (touched == 3 || touched == 4)
    {
        plyr.set_on_ground(false);
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
                    ++coins_collected;
                    game_map->get_tile_map()->at(x).at(y).set_value(0);
                }
                player.set_on_ground(true);
            }


            entity_collision(player, x, y, {PLAYER_WIDTH, PLAYER_HEIGHT});
        }
    }
}