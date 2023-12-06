#ifndef CONFIG_H
#define CONFIG_H

constexpr int DELAY_TIME = 10000;


namespace configurations
{
    void delay(int N=DELAY_TIME);
    namespace background_file_paths
    {
        constexpr const char *BACKGROUND_PATH = "textures/1330857.jpg";
        constexpr const char *PLAYER_LIFE_PATH = "textures/big_block.png";
    }
}


#endif