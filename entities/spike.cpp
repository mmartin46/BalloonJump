#include "spike.h"

Spike::Spike(int x, int y)
{
    set_stomped_on(false);
    set_x(x);
    set_y(y);
    set_dx(0);
    set_dy(0);
    sprites = std::vector<sf::Sprite>();
    frame = 0;

    // FIXME: Make a sprite sheet for the spike.
    init_sprites(ENEMY_WIDTH, ENEMY_HEIGHT,
                        SPIKE_DEFAULT_COLS,
                        "entities\\entity_sprites\\spike.png");
    set_on_ground(false);    
}


void Spike::move_up()
{
    this->set_dy(SPIKE_SPEED);
}

void Spike::move_down()
{
    this->set_dy(SPIKE_SPEED);
}

void Spike::update()
{
    ++timer;
    if ((timer % 100) < 50)
    {
        move_up();
    }
    else
    {
        move_down();
    }

    frame = SPIKE_FRAME;

    this->set_dx(this->get_x() + this->get_dx());
    this->set_dy(this->get_dy() + this->get_dy());
    sprites.at(frame).setPosition(get_x(), get_y());
}

void Spike::draw(sf::RenderWindow &window)
{
    sf::Sprite *curr_sprite = &sprites.at(frame);
    window.draw(*curr_sprite);
}