#ifndef HEADER_H
#define HEADER_H
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

constexpr int FONT_SIZE = 30;

constexpr int PLAYER_ICON_X = -190;
constexpr int PLAYER_ICON_Y = -10;

class GameHeader
{
    private:
        sf::Font font;
        sf::Text header_string;
        sf::Texture texture;
        sf::RenderWindow *window;
        sf::Sprite player_sprite;
    public:
        GameHeader(sf::RenderWindow *window, const char* font_file="Raleway-Medium.ttf");
        void set_sprite();
        inline void set_string(std::string str) { header_string.setString(str); };
        void draw();
        void scroll(int offset_x=0, int offset_y=0);
};

#endif