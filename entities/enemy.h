#ifndef ENEMY_H
#define ENEMY_H
#include "player.h"
#include <random>

constexpr int ENEMY_WIDTH = 16;
constexpr int ENEMY_HEIGHT = 16;
constexpr int ENEMY_SPEED = 2;

constexpr int ENEMY_DEFAULT_ROWS = 1;
constexpr int ENEMY_DEFAULT_COLS = 4;

namespace default_coordinates
{
    constexpr int DEFAULT_SAVED_X = 0;
    constexpr int DEFAULT_SAVED_Y = 0;
}

constexpr int STUCK_MOVING_LEFT = 1;
constexpr int STUCK_MOVING_RIGHT = 2;



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
        int is_stuck;
        std::pair<int, int> saved_position;
    public:
        explicit Enemy() = default;
        explicit Enemy(int x, int y);
        virtual void update() override;
        virtual void draw(sf::RenderWindow &window) override;

        int should_change_direction();

        virtual void init_sprites(int player_width, int player_height, int num_sprites, const char *file_name);

        void set_stomped_on(bool status) { stomped_on = status; }
        bool get_stomped_on() const { return stomped_on; }



        void move_left();
        void move_right();

        inline void set_saved_position() { saved_position.first = x; saved_position.second = y; }
        inline std::pair<int, int> get_saved_position() { return saved_position; }
        int get_is_stuck() override { return is_stuck; } const
        void set_is_stuck(int is_stuck) override { this->is_stuck = is_stuck; }
};


#endif