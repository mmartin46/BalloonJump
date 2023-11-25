#ifndef ENTITY_H
#define ENTITY_H
#pragma once

class Entity
{
    public:
        virtual double get_x() = 0;
        virtual void set_x(double x) = 0;
        virtual double get_y() = 0;
        virtual void set_y(double y) = 0;
};

#endif