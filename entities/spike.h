#ifndef SPIKE_H
#define SPIKE_H
#pragma once
#include "enemy.h"
#include <random>

constexpr int SPIKE_SPEED = 3;
constexpr int SPIKE_DEFAULT_ROWS = 1;
constexpr int SPIKE_DEFAULT_COLS = 1;

#define SPIKE_FRAME 0

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
        void adjust_position();
    public:
        explicit Spike();
        explicit Spike(int x, int y);
        void move_up();
        void move_down();
        void init_sprites(const char *file_name);
        void draw(sf::RenderWindow &window) override;
        void update() override;
};



#endif