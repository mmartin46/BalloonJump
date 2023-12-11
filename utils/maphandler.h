#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "map.h"
#include <unordered_map>
#include <vector>
#include <string>

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


#endif