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
        std::string id;
        int delay_time;
        std::pair<int,int> player_start_coordinates;
        const char *background_music_file;
        const char *tile_file_name;
    public:
        static int next_id;
        LevelSetting();
        LevelSetting(int, const std::pair<int, int> &player_start_coordinates, const char *, const char *);
        void set_delay_time(int time) { this->delay_time = time; }
        int get_delay_time() const { return delay_time; }

        void set_background_music_file(const char *background_music_file) { this->background_music_file = background_music_file; }
        const char *get_background_music_file() const { return background_music_file; }

        void set_tile_file_name(const char *tile_file_name) { this->tile_file_name = tile_file_name; }
        const char *get_tile_file_name() const { return tile_file_name; }

        void set_player_start_coordinates(std::pair<int, int> start_coords) { this->player_start_coordinates = start_coords; }
        std::pair<int, int> get_player_start_coordinates() const { return player_start_coordinates; } 
};



#endif