#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

constexpr int FONT_SIZE = 30;

class GameHeader
{
    private:
        sf::Font font;
        sf::Text header_string;
        sf::RenderWindow *window;
        sf::Sprite player_sprite;
    public:
        GameHeader(sf::RenderWindow *window, const char* font_file=nullptr);
        void set_sprite();
        inline void set_string(std::string str) { header_string.setString(str); };
        void draw();
};

void GameHeader::set_sprite()
{
    sf::Texture texture;
    if (!texture.loadFromFile("big_block.png"))
    {
        std::cerr << "GameHeader::set_sprite() -> Invalid File Name " << std::endl;
    }

    player_sprite.setTexture(texture);
    player_sprite.setPosition(20, 20);
    player_sprite.setScale(2.0, 2.0);
}

GameHeader::GameHeader(sf::RenderWindow *window, const char* font_file)
{
    this->window = window;
    if (!font.loadFromFile(font_file))
    {
        std::cerr << "GameHeader() -> Invalid File Name " << std::endl;
        exit(EXIT_FAILURE);
    }
    set_sprite();


    header_string.setFont(font);
    header_string.setCharacterSize(FONT_SIZE);
    header_string.setFillColor(sf::Color::White);
}

void GameHeader::draw()
{
    window->draw(player_sprite);
    window->draw(header_string);
}