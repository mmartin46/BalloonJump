// John 3:16
#include "map.h"
#include "player.h"
#include "map.h"
#include "background.h"
#include <memory>

#ifndef SCREEN_WIDTH
    #define SCREEN_WIDTH 1280
#endif

#ifndef SCREEN_HEIGHT
    #define SCREEN_HEIGHT 600
#endif



#define MAP_ROWS 48
#define MAP_COLUMNS 82

class Game
{
    private:
        sf::RenderWindow *window;
        sf::View game_view;
        std::shared_ptr<Player> player;
        std::shared_ptr<Background> background;

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
};

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

Game::Game(sf::RenderWindow *window, int width, int height, const char *file_name)
{
    this->window = window;
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
    background = std::make_shared<Background>("bg.png", *window);
}

void Game::draw()
{
    background->draw();

    player->draw(*window);
    game_map->draw();
}

void Game::update()
{
    player->update();
    collision_handler();
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

        configurations::delay();
        window.clear(sf::Color::White);

        game.draw();
        game.update();
        window.display();
    }
    return 0;
}