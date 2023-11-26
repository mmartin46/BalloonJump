#ifndef PLAYER_ATTRIBUTES_H
#define PLAYER_ATTRIBUTES_H
#pragma once

#include <stdexcept>
#include <iostream>

namespace attribs
{
    constexpr int COIN_COUNT = 0;
    constexpr int ENEMY_COUNT = 1;
    constexpr int CURR_HEALTH = 2;
}

class PlayerAttributes
{
    private:
        const int DEFAULT_HEALTH = 100;
        int health;
        int coins_collected;
        int enemies_destroyed;
    public:
        PlayerAttributes() : coins_collected(0), enemies_destroyed(0), health(DEFAULT_HEALTH) {}
        void inc_coin_count() { ++coins_collected; }
        void inc_enem_count() { ++enemies_destroyed; }
        void dec_health() { --health; }
        void reset_health() { health = DEFAULT_HEALTH; }
        
        int get_coin_count() const { return coins_collected; }
        int get_enem_count() const { return enemies_destroyed; }
        int get_health() const { return health; }

        bool is_dead() { return (health == 0); }

        int operator[] (int index) const;
};



#endif