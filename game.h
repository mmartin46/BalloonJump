#pragma once
#include "player.h"


// class Game
// {
//     private:
//         Player player;
//         sf::RenderWindow *window;
//         sf::Clock *clock;
//         sf::View view;
//     public:
//         Game(sf::RenderWindow *window);
//         Player* get_player() { return &player; }
//         sf::View* get_view() { return &view; }

//         void update();
//         void adjust_view();
//         void draw();
// };

// void Game::update()
// {
//     player.update();
// }

// void Game::adjust_view()
// {
//     view.setCenter(player.get_x(), player.get_y());

//     const float zoom_factor = 2.0f;
//     view.setSize(window->getSize().x / zoom_factor,
//                 window->getSize().y / zoom_factor);

//     window->setView(view);   
// }

// void Game::draw()
// {
//     player.draw(window);
// }

// Game::Game(sf::RenderWindow *window)
// {
//     this->window = window;
//     this->window->setView(view);

//     player = Player(100, 100);
//     player.create_sprite("aggie.png", this->window);
// }

