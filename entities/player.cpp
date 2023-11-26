#include "player.h"

void Player::apply_gravity(bool gravity_switch)
{
    if (gravity_switch == false)
    {
        
        set_dy(get_dy() + PLAYER_GRAVITY);
        if (get_dy() > 8)
        {
            set_dy(8);
        }
    }
}


void Player::jump()
{
    if (get_on_ground())
    {
        AudioHandler::get_instance().play_sound("jump_sound", 90.0F);
        AudioHandler::get_instance().print_sounds();

        set_on_ground(false);
        set_dy(JUMP_HEIGHT);
    }
}

void Player::update()
{
    ++timer;
    using sf::Keyboard;
    configurations::delay(FRAME_DELAY);

    // Check if the player is on the ground
    // if (get_on_ground())
    // {
    //     set_dy(0); // Stop falling
    // }

    if (Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        frame = PLAYER_JUMP_FRAME;
        this->jump();
    }

    if (Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        frame = PLAYER_RUNNING_FRAMES(timer);
        this->set_dx(-PLAYER_SPEED);
        facing_right = false;
    }
    else if (Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        frame = PLAYER_RUNNING_FRAMES(timer);
        this->set_dx(PLAYER_SPEED);
        facing_right = true;    
    }
    else if (!Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        frame = PLAYER_IDLE_FRAMES(timer);
        if (this->get_dx() > 0)
        {
            this->set_dx(this->get_dx() - 1);
        }
        else if (this->get_dx() < 0)
        {
            this->set_dx(this->get_dx() + 1);
        }
    }

    apply_gravity(get_on_ground());

    this->set_x(this->get_x() + this->get_dx());
    this->set_y(this->get_y() + this->get_dy());


    sprites.at(frame).setPosition(get_x(), get_y());

}

void Player::draw(sf::RenderWindow &window) 
{
    sf::Sprite *curr_sprite = &sprites.at(frame);
    if (!facing_right)
    {
        curr_sprite->setScale(-1, 1);
        curr_sprite->setPosition(get_x() + PLAYER_WIDTH, get_y());
    }
    else
    {
        curr_sprite->setScale(1, 1);
        curr_sprite->setPosition(get_x(), get_y());        
    }
    window.draw(*curr_sprite);
}

Player::Player(int x, int y)
{
    set_x(x);
    set_y(y);
    set_dx(0);
    set_dy(0);
    sprites = std::vector<sf::Sprite>();
    frame = 0;

    on_ground = false;
    init_sprites(PLAYER_WIDTH, PLAYER_HEIGHT, 
                PLAYER_DEFAULT_ROWS, PLAYER_DEFAULT_COLS);
    AudioHandler::get_instance().load_sound("jump_sound", "entities//jump.wav");
}
Player::Player()
{
    set_x(DEFAULT_PLAYER_X);
    set_y(DEFAULT_PLAYER_Y);
    set_dx(0);
    set_dy(0);
    sprites = std::vector<sf::Sprite>();
    frame = 0;

    on_ground = false;
    init_sprites(PLAYER_WIDTH, PLAYER_HEIGHT, 4, 4);
    AudioHandler::get_instance().load_sound("jump_sound", "entities//jump.wav");
}

void Player::init_sprites(int player_width, int player_height, 
                            int player_sprite_rows, int player_sprite_cols,
                            const char *file_name)
{
    sprites.clear();
    if (!texture.loadFromFile(file_name))
    {
        exit(1);
    }
    for (size_t x = 0; x < player_sprite_rows; ++x)
    {
        for (size_t y = 0; y < player_sprite_cols; ++y)
        {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sf::IntRect tileRect(y * PLAYER_WIDTH, x * PLAYER_HEIGHT, 
                                player_width, player_height);
            sprite.setTextureRect(tileRect);
            sprite.setPosition(get_x(), get_y());
            sprites.push_back(sprite);
        }
    }
}