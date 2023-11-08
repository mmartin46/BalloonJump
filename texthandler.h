#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

class TextHandler
{
    private:
        sf::Window *window_ptr;
        sf::Font font;
        sf::Text text;
        const char *font_file;
    public:
        void set_font_file(const char *font_file) { this->font_file = font_file; }
        const char *get_font_file() { return font_file; }

        TextHandler(const char *font_file, sf::Window *window);
};

TextHandler::TextHandler(const char *font_file, sf::Window *window)
{
    if (!font.loadFromFile(font_file))
    {
        std::cout << "TextHandler()-> invalid file name" << std::endl;
    }
    set_font_file(font_file);
    window_ptr = window;
    
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setString("test");
}

#endif