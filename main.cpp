#include <SFML/Graphics.hpp>
#include "game/game.h"
#include "utils/maphandler.h"


int main()
{ 

    sf::Texture tileset;
    if (!tileset.loadFromFile("textures/map1_tile_sheet.png"))
    {
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Test Game");
    MapHandler &map_handler = MapHandler::get_instance(window);

    Map map(&window, WORLD_MAP(0, 0).size(), WORLD_MAP(0, 0).at(0).size(),
            tileset, TILE_SIZE,
            &WORLD_MAP(0, 0), "textures/map1_tile_sheet.png",
            NUM_TILES + 1);
    ALL_WORLDS[WORLD_1].push_back(map);



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
        configurations::delay();
    }
    return 0;
}

