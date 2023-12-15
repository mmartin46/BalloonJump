#include "background.h"

void Background::scroll(float offset_x, float offset_y)
{
    sf::Vector2f curr_position = background_image.getPosition();
    background_image.setPosition(curr_position.x + offset_x, curr_position.y + offset_y);
}

Background::Background(const char *file_name, sf::RenderWindow &window)
{
    set_texture(file_name);
    this->window = &window;
}

void Background::set_texture(const char *file_name, int pos_x, int pos_y, float scale_x, float scale_y)
{
    if (!texture.loadFromFile(file_name))
    {
        std::cout << "Background(const char *) -> can't load image from given path\n";
        exit(EXIT_FAILURE);
    } 
    background_image = sf::Sprite(texture);
    background_image.setPosition(pos_x, pos_y);
    background_image.setScale(scale_x, scale_y);
}

void Background::draw()
{
    window->draw(background_image);
}