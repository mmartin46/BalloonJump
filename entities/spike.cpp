#include "spike.h"

Spike::Spike() : Spike(0, 0)
{
    sprites = std::vector<sf::Sprite>();
}

void Spike::init_sprites(const char *file_name)
{
    if (!texture.loadFromFile(file_name))
    {
        exit(1);
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprites.push_back(sprite);
}

Spike::Spike(int x, int y)
{
    set_stomped_on(false);
    set_x(x);
    set_y(y);
    set_dx(0);
    set_dy(0);
    sprites = std::vector<sf::Sprite>();
    frame = 0;

    init_sprites("entities\\entity_sprites\\spike.png");
    set_on_ground(false);
}

void Spike::adjust_position()
{
    static std::random_device rand_dev;
    static std::mt19937 engine(rand_dev());
    if (abs(get_y()) > 2000)
    {
        std::uniform_int_distribution<int> rand_y_dis(200, 400);
        set_y(rand_y_dis(engine));
    }
    if (abs(get_x() > 3000))
    {
        std::uniform_int_distribution<int> rand_x_dis(0, 3000);
    }
}

void Spike::move_up()
{
    this->set_dy(-SPIKE_SPEED);
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


    adjust_position();
    frame = SPIKE_FRAME;

    this->set_x(this->get_x() + this->get_dx());
    this->set_y(this->get_y() + this->get_dy());
    sprites.at(frame).setPosition(get_x(), get_y());
}

void Spike::draw(sf::RenderWindow &window)
{
    sf::Sprite *curr_sprite = &sprites.at(frame);
    window.draw(*curr_sprite);
}