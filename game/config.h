#ifndef CONFIG_H
#define CONFIG_H
#include <vector>

constexpr int DELAY_TIME = 6000;
constexpr int LARGE_MAP_DELAY_TIME = 1;


namespace configurations
{
    void delay(int N=DELAY_TIME);
    namespace background_file_paths
    {
        constexpr const char *BACKGROUND_PATH = "textures/back_drop_1.jpg";
        constexpr const char *PLAYER_LIFE_PATH = "textures/big_block.png";
    }

    namespace map_file_paths
    {
        extern std::vector<const char *> texture_file_paths;
    }
}


#endif