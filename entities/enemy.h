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

        bool stomped_on;
        bool on_ground;
        bool facing_right;
    public:
        explicit Enemy() = default;
        explicit Enemy(int x, int y);
        virtual void update() override;
        virtual void draw(sf::RenderWindow &window) override;

        virtual void init_sprites(int player_width, int player_height, int num_sprites, const char *file_name);

        void set_stomped_on(bool status) { stomped_on = status; }
        bool get_stomped_on() { return stomped_on; }
        void move_left();
        void move_right();
};


#endif