#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include "entity.h"
#include "playerattributes.h"
#include "../sounds/sounds.h"
#include "../game/config.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 600
#define HALF_SCREEN_WIDTH SCREEN_WIDTH / 2
#define HALF_SCREEN_HEIGHT SCREEN_HEIGHT / 2


constexpr int PLAYER_SPEED = 6;
constexpr int DEFAULT_PLAYER_X = 170;
constexpr int DEFAULT_PLAYER_Y = 0;
constexpr int PLAYER_GRAVITY = 2;
constexpr int JUMP_HEIGHT = -20;

// Sprite flipping
#define LEFT 1.0f
#define RIGHT -1.0f
#define INVERSE_POSITION -1, 1
#define DEFAULT_POSITION 1, 1

constexpr int PLAYER_WIDTH = 16;
constexpr int PLAYER_HEIGHT = 16;
constexpr int PLAYER_DEFAULT_ROWS = 4;
constexpr int PLAYER_DEFAULT_COLS = 4;

#define PLAYER_RUNNING_FRAMES(timer) (timer % 3) + 4
#define PLAYER_IDLE_FRAMES(timer) timer % 3
#define PLAYER_JUMP_FRAME 8

constexpr int FRAME_DELAY = 500;


class Player : public virtual Entity
{
    private:
        sf::Texture texture;
        std::vector<sf::Sprite> sprites;
        int x, y;
        double dx, dy;
        int frame;
        int timer = 0;

        bool on_ground;
        bool facing_right;
        bool is_jumping;
        int is_stuck;
    public:
        PlayerAttributes attributes;
        explicit Player();
        explicit Player(int x, int y);
        double get_x() override { return x; }
        void set_x(double x) override { this->x = x; }
        double get_y() override { return y; }
        void set_y(double y) override { this->y = y; }
        virtual void draw(sf::RenderWindow &window);

        sf::Sprite get_sprite() { return sprites.at(frame); }

        double get_dx() const { return this->dx; }
        void set_dx(double dx) { this->dx = dx; }
        double get_dy() const { return this->dy; }
        void set_dy(double dy) { this->dy = dy; }

        bool get_is_jumping() { return is_jumping; }
        void set_is_jumping(bool is_jumping) { this->is_jumping = is_jumping; }

        void set_on_ground(bool state) { on_ground = state; }
        bool get_on_ground() { return on_ground; }


        virtual int get_is_stuck() { return 0; } const
        virtual void set_is_stuck(int is_stuck) { }

        void allow_mini_jump();
        void jump();
        void apply_gravity(bool gravity_switch);
        virtual void update();
        void init_sprites(int player_width, int player_height, 
                        int player_sprite_rows, int player_sprite_cols, const char *file_name="entities\\entity_sprites\\aggie_trans.png");
};

#endif