// // John 3:16
// #include "game.h"

// #define SCREEN_WIDTH 400;
// #define SCREEN_HEIGHT 400;


// int main()
// {
//     sf::Texture texture;

//     if (!texture.loadFromFile("aggie.png"))
//     {
//         return -1;
//     }

//     Player player(300, 300);
    

//     sf::RenderWindow window(sf::VideoMode(600, 600), "Test Game");

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//             }
//         }
//         configurations::delay();
//         window.clear(sf::Color::White);
//         player.draw(window);
//         player.update();
//         window.display();
//     }
//     return 0;
// }