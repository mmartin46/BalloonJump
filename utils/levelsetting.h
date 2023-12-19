#ifndef LEVEL_SETTING_H
#define LEVEL_SETTING_H
#pragma once
#include <string>
#include <utility>
#include "../game/config.h"

constexpr int NUMBER_OF_MAPS = 3;
// FIXME: Finish and use this class 
// Easier way to handle the level settings
class LevelSetting
{
    private:
        std::vector<std::string> background_files;
        std::vector<std::string> tile_map_files;
        std::vector<std::string> music_files;
        LevelSetting();
    public:
        static LevelSetting& get_instance()
        {
            static LevelSetting instance;
            return instance;
        }
        void init_files();
        const char* get_background_file(int index) { return background_files.at(index).c_str(); }
        const char* get_map_file(int index) { return tile_map_files.at(index).c_str(); }
        const char* get_music_file(int index) { return music_files.at(index).c_str(); }
};




#endif