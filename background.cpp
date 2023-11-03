#pragma once
#include "entity.h"
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
        void set_texture(const char* file_name);
        void draw();
};

Background::Background(const char *file_name, sf::RenderWindow &window)
{
    set_texture(file_name);
    this->window = &window;
}

void Background::set_texture(const char *file_name)
{
    if (!texture.loadFromFile(file_name))
    {
        std::cout << "Background(const char *) -> can't load image from given path\n";
        exit(EXIT_FAILURE);
    } 
    background_image = sf::Sprite(texture);
}

void Background::draw()
{
    window->draw(background_image);
}