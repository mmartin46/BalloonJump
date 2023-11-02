// // John 3:16
// #include "map.h"


// #ifndef SCREEN_WIDTH
//     #define SCREEN_WIDTH 1280
// #endif

// #ifndef SCREEN_HEIGHT
//     #define SCREEN_HEIGHT 600
// #endif

// constexpr int DELAY_TIME = 10000;
// constexpr int FRAME_DELAY = 500;


// namespace configurations
// {
//     void delay(int N=DELAY_TIME)
//     {
//         for (int i = 0; i < N; i++)
//         {
//             for (int j = 0; j < N; j++);
//         }
//     }
// }


// int main()
// {

//     sf::Texture texture;

//     if (!texture.loadFromFile("tile_sheet.png"))
//     {
//         std::cerr << "FAILED TO LOAD" << std::endl;
//         exit(1);
//     }

   

//     sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Test Game");
//     Map map(&window, 48,
//                      82,
//                      texture, TILE_SIZE, &world::coordinate_map, "tile_sheet.png",
//                      NUM_TILES);


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

//         map.draw();
//         window.display();
//     }
//     return 0;
// }