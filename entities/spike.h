#ifndef SPIKE_H
#define SPIKE_H
#pragma once
#include "enemy.h"

constexpr int SPIKE_SPEED = 10;
constexpr int SPIKE_DEFAULT_ROWS = 1;
constexpr int SPIKE_DEFAULT_COLS = 1;

// FIXME: Not finished
class Spike : public Enemy
{
    private:
        sf::Texture texture;
        std::vector<sf::Sprite> sprites;
        int x, y;
        double dx, dy;
        int frame;
        int timer = 0;

        bool stomped_on;
        bool on_ground;
        bool facing_right;
    public:
        explicit Spike() : Spike(0, 0) {};
        explicit Spike(int x, int y);
        void move_up();
        void move_down();
        void draw(sf::RenderWindow &window) override;
        void update() override;
};



#endif