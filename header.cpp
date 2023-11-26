#include "header.h"

void GameHeader::scroll(int offset_x, int offset_y)
{
    player_sprite.move(offset_x, offset_y);
    header_string.move(offset_x, offset_y);
}

void GameHeader::set_sprite()
{
    if (!texture.loadFromFile("big_block.png"))
    {
        std::cerr << "GameHeader::set_sprite() -> Invalid File Name " << std::endl;
    }

    player_sprite.setTexture(texture);
    player_sprite.setPosition(PLAYER_ICON_X, PLAYER_ICON_Y);
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
    header_string.setPosition(PLAYER_ICON_X + 100, PLAYER_ICON_Y);
}

void GameHeader::draw()
{
    window->draw(player_sprite);
    window->draw(header_string);
}