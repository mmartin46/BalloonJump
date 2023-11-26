#include "playerattributes.h"

int PlayerAttributes::operator[] (int index) const
{
    switch (index)
    {
        case attribs::COIN_COUNT:
            return coins_collected;
        case attribs::ENEMY_COUNT:
            return enemies_destroyed;
        case attribs::CURR_HEALTH:
            return health;
        default:
            throw std::out_of_range("Invalid index");
    }
}