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
}
