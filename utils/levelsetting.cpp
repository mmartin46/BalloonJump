#include "levelsetting.h"

LevelSetting::LevelSetting()
{
    init_files();
}

void LevelSetting::init_files()
{
    background_files = std::vector<std::string>();
    tile_map_files = std::vector<std::string>();
    music_files = std::vector<std::string>();

    for (int i = 1; i <= NUMBER_OF_MAPS; ++i)
    {
        std::string back_file = "textures/back_drop_" + std::to_string(i) + ".jpg";
        std::string map_file = "textures/map" + std::to_string(i) + "_tile_sheet.png";
        std::string music_file = "sounds/bg_music_" + std::to_string(i) + ".mp3";

        background_files.push_back(back_file);
        tile_map_files.push_back(map_file);
        music_files.push_back(music_file);
    }
}