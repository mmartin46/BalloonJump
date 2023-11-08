#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include "entity.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 600


constexpr int PLAYER_SPEED = 6;
constexpr int DEFAULT_PLAYER_X = 250;
constexpr int DEFAULT_PLAYER_Y = 0;
constexpr int PLAYER_GRAVITY = 2;
constexpr int JUMP_HEIGHT = -20;

// Sprite flipping
#define LEFT 1.0f
#define RIGHT -1.0f


constexpr int PLAYER_WIDTH = 16;
constexpr int PLAYER_HEIGHT = 16;
constexpr int PLAYER_DEFAULT_ROWS = 4;
constexpr int PLAYER_DEFAULT_COLS = 4;

#define PLAYER_RUNNING_FRAMES(timer) (timer % 3) + 4
#define PLAYER_IDLE_FRAMES(timer) timer % 3


constexpr int DELAY_TIME = 10000;
constexpr int FRAME_DELAY = 500;

namespace configurations
{
    void delay(int N=DELAY_TIME)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++);
        }
    }
}

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
    public:
        Player();
        Player(int x, int y);
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
        void jump();
        void apply_gravity(bool gravity_switch);
        virtual void update();
        void init_sprites(int player_width, int player_height, 
                        int player_sprite_rows, int player_sprite_cols, const char *file_name="aggie_trans.png");
};

void Player::apply_gravity(bool gravity_switch)
{
    if (gravity_switch)
    {
        
        set_dy(get_dy() + PLAYER_GRAVITY);
        if (get_dy() > 8)
        {
            set_dy(8);
        }
    }
}


void Player::jump()
{
    if (get_on_ground() && !is_jumping)
    {
        set_dy(JUMP_HEIGHT);
        is_jumping = true;
    }
}

void Player::update()
{
    ++timer;
    using sf::Keyboard;
    configurations::delay(FRAME_DELAY);

    if (Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        frame = 8;
        this->jump();
    }

    if (Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        frame = PLAYER_RUNNING_FRAMES(timer);
        this->set_dx(-PLAYER_SPEED);
        facing_right = false;
    }
    else if (Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        frame = PLAYER_RUNNING_FRAMES(timer);
        this->set_dx(PLAYER_SPEED);
        facing_right = true;    
    }
    else if (!Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        frame = PLAYER_IDLE_FRAMES(timer);
        if (this->get_dx() > 0)
        {
            this->set_dx(this->get_dx() - 1);
        }
        else if (this->get_dx() < 0)
        {
            this->set_dx(this->get_dx() + 1);
        }
    }


    apply_gravity(get_on_ground());




    this->set_x(this->get_x() + this->get_dx());
    this->set_y(this->get_y() + this->get_dy());

    // std::cout << "player()->dy" <<this->get_dy() << std::endl;
    // std::cout << "player()->is_jumping " <<this->get_is_jumping() << std::endl;
    // std::cout << "player()->is_pn_ground " <<this->get_on_ground() << std::endl;


    sprites.at(frame).setPosition(get_x(), get_y());

}

void Player::draw(sf::RenderWindow &window) 
{
    sf::Sprite *curr_sprite = &sprites.at(frame);
    if (!facing_right)
    {
        curr_sprite->setScale(-1, 1);
        curr_sprite->setPosition(get_x() + PLAYER_WIDTH, get_y());
    }
    else
    {
        curr_sprite->setScale(1, 1);
        curr_sprite->setPosition(get_x(), get_y());        
    }
    window.draw(*curr_sprite);
}

Player::Player(int x, int y)
{
    set_x(x);
    set_y(y);
    set_dx(0);
    set_dy(0);
    sprites = std::vector<sf::Sprite>();
    frame = 0;

    init_sprites(PLAYER_WIDTH, PLAYER_HEIGHT, 
                PLAYER_DEFAULT_ROWS, PLAYER_DEFAULT_COLS);
}
Player::Player()
{
    set_x(DEFAULT_PLAYER_X);
    set_y(DEFAULT_PLAYER_Y);
    set_dx(0);
    set_dy(0);
    sprites = std::vector<sf::Sprite>();
    frame = 0;

    init_sprites(PLAYER_WIDTH, PLAYER_HEIGHT, 4, 4);
}

void Player::init_sprites(int player_width, int player_height, 
                            int player_sprite_rows, int player_sprite_cols,
                            const char *file_name)
{
    if (!texture.loadFromFile(file_name))
    {
        exit(1);
    }
    for (size_t x = 0; x < player_sprite_rows; ++x)
    {
        for (size_t y = 0; y < player_sprite_cols; ++y)
        {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sf::IntRect tileRect(y * PLAYER_WIDTH, x * PLAYER_HEIGHT, 
                                player_width, player_height);
            sprite.setTextureRect(tileRect);
            sprite.setPosition(get_x(), get_y());
            sprites.push_back(sprite);
        }
    }
}