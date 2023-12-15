#ifndef LEVEL_SETTING_H
#define LEVEL_SETTING_H
#pragma once
#include <string>
#include <utility>
#include "../game/config.h"

// FIXME: Finish and use this class 
// Easier way to handle the level settings
class LevelSetting
{
    private:
        static int next_id;
        std::string id;
        int delay_time;
        std::pair<int,int> player_start_coordinates;
        const char *background_music_file;
        const char *tile_file_name;
    public:
        LevelSetting();
        LevelSetting(int, const std::pair<int, int> &player_start_coordinates, const char *, const char *);
};

int LevelSetting::next_id = 0;

LevelSetting::LevelSetting()
{
    id = next_id++;
    delay_time = DELAY_TIME;
    player_start_coordinates = {0, 0};
    background_music_file = nullptr;
    tile_file_name = nullptr;
}

LevelSetting::LevelSetting(int delay_time, 
                            const std::pair<int, int> &player_start_coordinates, 
                            const char *background_music_file,
                            const char *tile_file_name)
{
    id = next_id++;
    this->delay_time = delay_time;
    this->player_start_coordinates = player_start_coordinates;
    this->background_music_file = background_music_file;
    this->tile_file_name = tile_file_name;
}

#endif