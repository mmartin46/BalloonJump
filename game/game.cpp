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
    using namespace configurations;
    using namespace music_settings;
    background = std::make_shared<Background>(background_file_paths::BACKGROUND_PATH, *window);
    enemy_handler = EnemyHandler(window);
    set_game_over(false);
    level_complete = false;


    AudioHandler::get_instance().play_music(music_file_paths::LEVEL_ONE_MUSIC, music_settings::BACKGROUND_MUSIC_VOLUME);

    header.set_string("Health x" + (to_string(player.attributes[attribs::CURR_HEALTH])) + "\tCoins x" + (to_string(player.attributes[attribs::COIN_COUNT]) + "\tEnemies x" + (to_string(player.attributes[attribs::ENEMY_COUNT]))));

    enemy_handler.allocate_enemies(ENEMY_COUNT, MIN_ENEMY_X, MAX_ENEMY_X, MIN_ENEMY_Y, MAX_ENEMY_Y);
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

void Game::player_enemy_collision_handling()
{
    enemy_handler.update_enemies(&player);
    enemy_handler.update_stomped_enemies(&player);
    collision_handler();
    enemy_collision_handler();

    if (player_landed_on_enemy(player, {PLAYER_WIDTH, PLAYER_HEIGHT}))
    {
        player.allow_mini_jump();
    }
}

void Game::update()
{
    player.update();
    player_enemy_collision_handling();


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
    handle_game_over();
    game_view.setCenter(get_player().get_x() + PLAYER_WIDTH / 2, get_player().get_y() + PLAYER_HEIGHT / 2);
}


void Game::handle_game_over()
{
    // If the player's health is 0 or less set the game over variable to true.
    if (player.attributes.get_health() <= 0)
    {
        set_game_over(true);
    }

    if (is_game_over())
    {
        // FIXME: Make a proper handling of a game over.
        exit(1);
    }
}

// If the player beat the level swap to a different map.
void Game::change_game_map(Map *new_map)
{
    if (level_complete)
    {
        game_map = new_map;
        level_complete = false;
        // FIXME: Also swap the background music.
    }
}

// Roomate Suggestion
// FIXME: Add a Manhattan distance ( off-screen ) function between a player and enemy
// When they aren't on the screen get rid of them.