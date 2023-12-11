#include "game.h"

bool Game::player_landed_on_enemy(Player &plyr, const std::pair<int, int> &dim)
{
    int touched = 0;
    Matrix<Tile> &tiles = *game_map->get_tile_map();
    float pw = dim.first, ph = dim.second;
    float px = plyr.get_x(), py = plyr.get_y();
    bool player_landed_on_enemy = false;

    for (auto &enemy : *enemy_handler.get_enemies())
    {
        float ex = enemy->get_x();
        float ey = enemy->get_y();
        float ew = ENEMY_WIDTH;
        float eh = ENEMY_HEIGHT;

        bool collide_x = px + pw > ex && px < ex + ew;
        bool collide_y = py + ph > ey && py < ey + eh;

        if (px + pw > ex && px < ex + ew && py + ph > ey && py < ey)
        {
            using namespace music_settings;
            AudioHandler::play_sound(sound_file_paths::ENEMY_STOMP_SOUND);
            player.attributes.inc_enem_count();
            enemy->set_stomped_on(true);
            player_landed_on_enemy = true;
            continue;
        }

        // If the player didn't land on them but touching 
        // decrease the health.
        sf::FloatRect enemy_bound_box(ex, ey, ew, eh);
        sf::FloatRect player_bound_box(px, py, pw, ph);
        if (player_bound_box.intersects(enemy_bound_box))
        {
            player.attributes.dec_health();
        }

    }
    return player_landed_on_enemy;

}


int Game::entity_collision(Player &plyr, int i, int j, std::pair<int, int> dim)
{
    int touched = 0;
    Matrix<Tile> &tiles = *game_map->get_tile_map();
    float pw = dim.first, ph = dim.second;
    float px = plyr.get_x(), py = plyr.get_y();
    float bx = tiles.at(i).at(j).get_x(), by = tiles.at(i).at(j).get_y();
    float bw = TILE_SIZE, bh = TILE_SIZE;

    const int TOP_EDGE = 1;
    const int BOTTOM_EDGE = 2;
    const int RIGHT_EDGE = 3;
    const int LEFT_EDGE = 4;
    const int COIN_VALUE = 5;

    if ((tiles.at(i).at(j).get_value() == 0) || (tiles.at(i).at(j).get_value() == COIN_VALUE))
    {
        return 0;
    }

    // Allow the enemy to move through coins
    Enemy *enemy = dynamic_cast<Enemy*>(&plyr);
    if (enemy && (tiles.at(i).at(j).get_value() == COIN_VALUE))
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
            touched = TOP_EDGE;
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
            touched = BOTTOM_EDGE;
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
            touched = RIGHT_EDGE;
            if (enemy)
            {
                enemy->set_is_stuck(STUCK_MOVING_RIGHT);
            }
        }
        // Rubbing against left edge
        else if (px+pw > bx && px < bx && plyr.get_dx() > 0)
        {
            // correct x
            plyr.set_x(bx-pw);
            px = bx-pw;

            plyr.set_dx(0);
            touched = LEFT_EDGE;
            if (enemy)
            {
                enemy->set_is_stuck(STUCK_MOVING_LEFT);
            }
        }
    }

    if (touched == RIGHT_EDGE || touched == LEFT_EDGE)
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
                    using namespace music_settings;
                    AudioHandler::play_sound(sound_file_paths::COIN_COLLECT_SOUND);
                    player.attributes.inc_coin_count();
                    game_map->get_tile_map()->at(x).at(y).set_value(0);
                }
                player.set_on_ground(true);
            }

            entity_collision(player, x, y, {PLAYER_WIDTH, PLAYER_HEIGHT});
        }
    }
}