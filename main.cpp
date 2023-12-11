#include <SFML/Graphics.hpp>
#include "game/game.h"
#include "utils/maphandler.h"

using std::string;

const string WORLD_1 = "world_1";

class MapHandler
{
    private:
        MapHandler(sf::RenderWindow &);
    public:
        static MapHandler& get_instance(sf::RenderWindow &window);
        std::unordered_map<std::string, vector<Map>> world_maps;
};

MapHandler::MapHandler(sf::RenderWindow &window)
{
    world_maps.insert({WORLD_1, vector<Map>()});
}

MapHandler& MapHandler::get_instance(sf::RenderWindow &window)
{
    static MapHandler map_handler(window);
    return map_handler;
}

#define ALL_WORLDS map_handler.world_maps


int main()
{ 

    sf::Texture tileset;
    if (!tileset.loadFromFile("textures/map1_tile_sheet.png"))
    {
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Test Game");
    MapHandler &map_handler = MapHandler::get_instance(window);

    Map map(&window, world::coordinate_map.size(), world::coordinate_map.at(0).size(),
            tileset, TILE_SIZE,
            &world::coordinate_map, "textures/map1_tile_sheet.png",
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