#include "game.h"

void Game::init_current_level()
{
    current_level.first = 0;
    current_level.second = 0;
}

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

void Game::player_reset_position(Player &player)
{
    player.set_x(DEFAULT_PLAYER_X);
    player.set_y(DEFAULT_PLAYER_Y);
}

void Game::player_reset_assets(Player &player)
{
    player.attributes.reset_health();
    player.attributes.set_coin_count(DEFAULT_COIN_COLLECT_COUNT);
    player.attributes.set_enem_count(DEFAULT_ENEMY_DESTROY_COUNT);
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
    change_game_map();

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
void Game::change_game_map()
{
    if (player.attributes.get_coin_count() >= PLAYER_COIN_LIMIT)
    {
        level_complete = true;
        //std::cout << "Game::change_game_map(): Player has enough coins" << std::endl;
    }
    if (level_complete)
    {
        // FIXME: Also swap the background music.
        try
        {
            if ((current_level.second + 1) < world::world_maps.at(current_level.first).size())
            {
                std::cout << "Game::change_game_map(): Changing map";
                
                game_map->set_tile_file_name("textures/map2_tile_sheet.png");
                game_map->set_tile_map(WORLD_MAP(current_level.first, ++current_level.second));
                game_map->init_sprites(TILE_SIZE);
                player_reset_position(player);
                player_reset_assets(player);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        level_complete = false;
    }
}

