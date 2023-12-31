#ifndef MAP_H
#define MAP_H
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "tile.h"
using std::vector;
template <typename T>
using Matrix = vector<vector<T>>;

constexpr int TILE_SIZE = 20;
constexpr int NUM_TILES = 24;

// Holds all the coordinates for each map.
namespace world
{
    extern Matrix<Matrix<int>> world_maps;
}

// Loads a map from a matrix of integers
class Map
{
    private:
        int rows;
        int columns;
        int tile_size;
        const char *file_name;
        int number_of_tiles;


        // Integer positions of the tiles
        Matrix<Tile> tile_map;
        // Coordinates of the tiles

        sf::Texture tileset;
        vector<sf::Sprite> tile_sprites;

        sf::RenderWindow *window;
    public:
        void init_sprites(int tile_size);
        void init_map(int tile_size, Matrix<int> *tile_map);
        void set_number_of_tiles(int number_of_tiles) { this->number_of_tiles = number_of_tiles; }
        int get_number_of_tiles() { return number_of_tiles; }

        void set_rows(int rows) { this->rows = rows; }
        int get_rows() { return rows; }

        void set_columns(int columns) { this->columns = columns; }
        int get_columns() { return columns; }

        void set_tile_size(int tile_size) {
            this->tile_size = tile_size;
        }
        int get_tile_size() { return tile_size; }
        
        sf::Texture get_tile_set() { return tileset; }

        void set_tile_file_name(const char* file_name) 
        { 
            this->file_name = file_name;
            if (!tileset.loadFromFile(file_name)) 
            {
                throw std::runtime_error("Invalid file");
            }
        }


        Map();
        Map(sf::RenderWindow *window, int rows, int cols, int tile_size,
                            vector<vector<int>> *tile_map, const char *file_name, int number_of_tiles);

        Matrix<Tile>* get_tile_map() { return &tile_map; }
        void set_tile_map(const Matrix<int> &tile_map);
        void draw();
};

#endif