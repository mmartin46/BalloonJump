#include "header.h"

void GameHeader::scroll(int offset_x, int offset_y)
{
    player_sprite.setPosition((offset_x) - 300, offset_y - 120);
    header_string.setPosition((offset_x + 40) - 300, offset_y - 120);
}

void GameHeader::set_sprite()
{
    using namespace configurations;
    if (!texture.loadFromFile(configurations::background_file_paths::PLAYER_LIFE_PATH))
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
    header_string.setPosition(PLAYER_ICON_X + ICON_TO_STR_OFFSET, PLAYER_ICON_Y);
}

void GameHeader::draw()
{
    window->draw(player_sprite);
    window->draw(header_string);
}