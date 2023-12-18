#include "config.h"

namespace configurations
{
    void delay(int N)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++);
        }
    }
    namespace map_file_paths
    {
        std::vector<const char *> texture_file_paths = {
            "textures/map1_tile_sheet.png",
            "textures/map2_tile_sheet.png"
        };
    }
}
