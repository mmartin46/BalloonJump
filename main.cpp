// John 3:16
#include "map.h"
#include "player.h"
#include "map.h"
#include "background.h"
#include "enemyhandler.h"
#include <memory>
#include <random>

#ifndef SCREEN_WIDTH
    #define SCREEN_WIDTH 1280
#endif

#ifndef SCREEN_HEIGHT
    #define SCREEN_HEIGHT 600
#endif


constexpr int ENEMY_COUNT = 1;

#define MAP_ROWS 48
#define MAP_COLUMNS 82

class Game
{
    private:
        sf::RenderWindow *window;
        sf::View game_view;
        std::shared_ptr<Player> player;
        std::shared_ptr<Background> background;


        EnemyHandler enemy_handler;

        std::shared_ptr<Map> game_map;
        sf::Texture map_sprite_texture;
    public:
        Game(sf::RenderWindow *window, int width, int height, const char *file_name);
        std::shared_ptr<Player> get_player() { return player; }
        void update();
        void draw();
        void set_background(const char *background_file_path);

        int entity_collision(Player &plyr, int i, int j, std::pair<int, int> dim);
        void collision_handler();

        bool check_tile_collision(const sf::Sprite &sprite, const sf::Sprite &tile_sprite);
        void enemy_collision_handler();

        bool player_landed_on_enemy(Player &plyr, std::pair<int, int> dim);
};

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

bool Game::check_tile_collision(const sf::Sprite &sprite, const sf::Sprite &tile_sprite)
{
    sf::FloatRect sprite_bounds = sprite.getGlobalBounds();
    sf::FloatRect tile_bounds = tile_sprite.getGlobalBounds();

    return sprite_bounds.intersects(tile_bounds);
}

void Game::set_background(const char *background_file_path)
{
    background->set_texture(background_file_path);
}

int Game::entity_collision(Player &plyr, int i, int j, std::pair<int, int> dim)
{
    int touched = 0;
    Matrix<Tile> &tiles = *game_map->get_tile_map();
    float pw = dim.first, ph = dim.second;
    float px = plyr.get_x(), py = plyr.get_y();
    float bx = tiles.at(i).at(j).get_x(), by = tiles.at(i).at(j).get_y();
    float bw = TILE_SIZE, bh = TILE_SIZE;

    if (tiles.at(i).at(j).get_value() == 0)
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
            // plyr.set_on_ground(false);
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
            plyr.set_is_jumping(false);
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

void Game::collision_handler()
{
    int x, y;
    for (x = 0; x < MAP_ROWS; ++x)
    {
        for (y = 0; y < MAP_COLUMNS; ++y)
        {
            Tile *current_tile = &game_map->get_tile_map()->at(x).at(y);
            if (check_tile_collision(get_player()->get_sprite(), *current_tile->get_sprite()))
            {
                // Check for a coin
                if (current_tile->get_value() == 5)
                {
                    game_map->get_tile_map()->at(x).at(y).set_value(0);
                }
            }


            entity_collision(*get_player(), x, y, {PLAYER_WIDTH, PLAYER_HEIGHT});
        }
    }
}

void Game::enemy_collision_handler()
{
    int x, y, z;
    for (x = 0; x < MAP_ROWS; ++x)
    {
        for (y = 0; y < MAP_COLUMNS; ++y)
        {
            for (auto &enemy : *enemy_handler.get_enemies())
            {
                entity_collision(*enemy, x, y, {ENEMY_WIDTH, ENEMY_HEIGHT});            
            }
        }
    }    
}

Game::Game(sf::RenderWindow *window, int width, int height, const char *file_name)
{
    this->window = window;
    enemy_handler = EnemyHandler(window);
    if (!map_sprite_texture.loadFromFile(file_name))
    {
        std::cerr << "Game(): Failed to load tile sheet." << std::endl;
        exit(1);
    }

    player = std::make_shared<Player>();
    game_map = std::make_shared<Map>(window, MAP_ROWS, MAP_COLUMNS,
                                map_sprite_texture, TILE_SIZE,
                                &world::coordinate_map, file_name,
                                NUM_TILES);
    background = std::make_shared<Background>("1330857.jpg", *window);
    
    enemy_handler.allocate_enemies(10, 800, 800);
}

void Game::draw()
{
    background->draw();

    player->draw(*window);
    enemy_handler.draw_enemies();
    game_map->draw();
}

void Game::update()
{
    player->update();
    enemy_handler.update_enemies();
    collision_handler();
    enemy_collision_handler();

    // Testing
    if (player_landed_on_enemy(*get_player(), {PLAYER_WIDTH, PLAYER_HEIGHT}))
    {
        player->set_dy(JUMP_HEIGHT / 2);
    }
}



int main()
{ 

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Test Game");
    Game game(&window, SCREEN_WIDTH, SCREEN_HEIGHT, "tile_sheet.png");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        configurations::delay(DELAY_TIME-1000);
        window.clear(sf::Color::White);

        game.draw();
        game.update();
        window.display();
    }
    return 0;
}