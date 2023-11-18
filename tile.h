#pragma once
#include "entities/entity.h"


class Tile : public virtual Entity
{
    private:
        int x, y;
        sf::Sprite sprite;
        int value;
    public:
        void set_sprite(sf::Sprite sprite) { this->sprite = sprite; }
        sf::Sprite* get_sprite() { return &sprite; }

        void set_value(int value) { this->value = value; }
        int get_value() { return value; }

        double get_x() override { return x; }
        void set_x(double x) override { this->x = x;}
        double get_y() override { return y; }
        void set_y(double y) override { this->y = y; }
        Tile();
        Tile(int value, int x, int y);
};

Tile::Tile() : value(0), x(0), y(0)
{
}

Tile::Tile(int value, int x, int y) : value(value), x(x), y(y)
{
}