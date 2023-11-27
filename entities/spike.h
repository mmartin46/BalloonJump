#ifndef SPIKE_H
#define SPIKE_H
#pragma once
#include "enemy.h"

class Spike : public Enemy
{
    public:
        explicit Spike() = default;
        void update() override;
};

#endif