#ifndef BACKGROUND_H
#define BACKGROUND_H
#pragma once
#include "../entities/entity.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Background
{
    private:
        sf::Texture texture;
        sf::Sprite background_image;
        sf::RenderWindow *window;
    public:
        Background(const char *file_name, sf::RenderWindow &window);
        sf::Sprite get_background_image() { return background_image; }
        void set_texture(const char *file_name, int pos_x=-230, int pos_y=0, float scale_x=1.2f, float scale_y=1.2f);
        void draw();
        void scroll(float offset_x, float offset_y);
};

#endif