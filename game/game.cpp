#include "game.h"

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

    background = std::make_shared<Background>("textures/1330857.jpg", *window);
    enemy_handler = EnemyHandler(window);

    header.set_string("Health x" + (to_string(player.attributes[attribs::CURR_HEALTH])) + "\tCoins x" + (to_string(player.attributes[attribs::COIN_COUNT]) + "\tEnemies x" + (to_string(player.attributes[attribs::ENEMY_COUNT]))));

    enemy_handler.allocate_enemies(ENEMY_COUNT, 1000, MAX_ENEMY_X, -3000, MAX_ENEMY_Y);
    game_view.setSize(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}


void Game::draw()
{

    header.set_string("Health x" + (to_string(player.attributes[attribs::CURR_HEALTH])) + "\tCoins x" + (to_string(player.attributes[attribs::COIN_COUNT]) + "\tEnemies x" + (to_string(player.attributes[attribs::ENEMY_COUNT]))));
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
    header.scroll(player.get_x(), player.get_y());
    // Testing
    if (player_landed_on_enemy(player, {PLAYER_WIDTH, PLAYER_HEIGHT}))
    {
        player.set_dy(JUMP_HEIGHT / 2);
    }


    game_view.setCenter(get_player().get_x() + PLAYER_WIDTH / 2, get_player().get_y() + PLAYER_HEIGHT / 2);
}
