#include <SFML/Graphics.hpp>
#include "game/game.h"
#include "utils/maphandler.h"

constexpr int NUM_MAPS = 2;

int main()
{ 

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Test Game");
    MapHandler &map_handler = MapHandler::get_instance(window);


    Map map(&window, WORLD_MAP(0, 0).size(), WORLD_MAP(0, 0).at(0).size(), TILE_SIZE,
            &WORLD_MAP(0, 0), LevelSetting::get_instance().get_map_file(0),
            NUM_TILES + 1);
    ALL_WORLDS[WORLD_1].push_back(map);

    for (int map_index = 1; map_index < NUM_MAPS; ++map_index)
    {
        string map_texture_path = "textures/map" + to_string(map_index + 1) + "_tile_sheet.png";
        ALL_WORLDS[WORLD_1].push_back(Map(&window, WORLD_MAP(0, map_index).size(), 
                                        WORLD_MAP(0, map_index).at(0).size(), TILE_SIZE,
                                        &WORLD_MAP(0, map_index), map_texture_path.c_str(),
                                        NUM_TILES + 1));
    }

    Game game(&window, &ALL_WORLDS[WORLD_1].at(0));

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
        game.update();

        window.clear();

        game.draw();

        //std::cout << game.get_player().get_on_ground() << std::endl;
        window.display();
        configurations::delay(game.get_delay_speed());
    }
    return 0;
}

