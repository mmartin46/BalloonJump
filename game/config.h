#ifndef CONFIG_H
#define CONFIG_H

constexpr int DELAY_TIME = 100;
constexpr int LARGE_MAP_DELAY_TIME = 1;


namespace configurations
{
    void delay(int N=DELAY_TIME);
    namespace background_file_paths
    {
        constexpr const char *BACKGROUND_PATH = "textures/back_drop_1.jpg";
        constexpr const char *PLAYER_LIFE_PATH = "textures/big_block.png";
    }
}


#endif