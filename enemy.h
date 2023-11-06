#ifndef ENEMY_H
#define ENEMY_H
#include "player.h"

constexpr int ENEMY_WIDTH = 16;
constexpr int ENEMY_HEIGHT = 16;
constexpr int ENEMY_SPEED = 2;

constexpr int ENEMY_DEFAULT_ROWS = 1;
constexpr int ENEMY_DEFAULT_COLS = 4;

#define ENEMY_FRAMES(timer) timer % 4

class Enemy : public Player
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
        Enemy(int x, int y);
        void update() override;
        void draw(sf::RenderWindow &window) override;

        void init_sprites(int player_width, int player_height, int num_sprites, const char *file_name);

        void move_left();
        void move_right();
};

Enemy::Enemy(int x, int y)
{
    set_x(x);
    set_y(y);
    set_dx(0);
    set_dy(0);
    sprites = std::vector<sf::Sprite>();
    frame = 0;

    init_sprites(ENEMY_WIDTH, ENEMY_HEIGHT,
                        ENEMY_DEFAULT_COLS,
                        "enemy.png");
    set_on_ground(false);
    set_is_jumping(true);
}

void Enemy::move_left()
{
    facing_right = false;
    this->set_dx(-ENEMY_SPEED);
}

void Enemy::move_right()
{
    facing_right = true;
    this->set_dx(ENEMY_SPEED);
}

void Enemy::update()
{
    ++timer;
    if ((timer % 100) < 50)
    {
        move_right();
    }
    else
    {
        move_left();
    }

    apply_gravity(true);
    this->set_x(this->get_x() + this->get_dx());
    this->set_y(this->get_y() + this->get_dy());

    // Goes out of scope
    if (this->get_x() > SCREEN_WIDTH)
    {
        this->set_x(0);
    }
    if (this->get_y() > SCREEN_HEIGHT)
    {
        this->set_y(0);
    }

    frame = ENEMY_FRAMES(timer);
    sprites.at(frame).setPosition(get_x(), get_y());
}


void Enemy::draw(sf::RenderWindow &window) 
{
    sf::Sprite *curr_sprite = &sprites.at(frame);
    if (!facing_right)
    {
        curr_sprite->setScale(-1, 1);
        curr_sprite->setPosition(get_x() + ENEMY_WIDTH, get_y());
    }
    else
    {
        curr_sprite->setScale(1, 1);
        curr_sprite->setPosition(get_x(), get_y());        
    }
    window.draw(*curr_sprite);
}

void Enemy::init_sprites(int player_width, int player_height, int num_sprites, const char *file_name)
{
    // FIXME: Not finished
    if (!texture.loadFromFile(file_name))
    {
        exit(1);
    }

    for (size_t x = 0; x < num_sprites; ++x)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sf::IntRect tileRect(x * ENEMY_HEIGHT, 1, player_width, player_height);
        sprite.setTextureRect(tileRect);
        sprite.setPosition(get_x(), get_y());

        sprites.push_back(sprite);
    }
}

#endif