#include <SFML/Graphics.hpp>
#include "game.h"

namespace GameMaps
{
    static vector<Map> maps;
}

int main()
{ 
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Test Game");

    sf::Texture tileset;
    if (!tileset.loadFromFile("textures/tile_sheet.png"))
    {
        return -1;
    }

    Map map(&window, world::coordinate_map.size(), world::coordinate_map.at(0).size(),
            tileset, TILE_SIZE,
            &world::coordinate_map, "textures/tile_sheet.png",
            NUM_TILES + 1);

    GameMaps::maps.push_back(map);
    

    Game game(&window, &GameMaps::maps.at(0));

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