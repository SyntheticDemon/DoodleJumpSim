#include "player.hpp"
#include "camera.hpp"
#include "platform.hpp"
#include <string>
#define FONT "assets/gamefont.ttf"
#define FONT_SIZE 30
#define HORIZONTAL_VELOICTY 5
#define D 'd'
#define A 'a'
#define LOSE "You lose"
void Player::strafe_right()
{
    velocity->x = HORIZONTAL_VELOICTY;
    right_facing=true;
}
void Player ::strafe_left()
{
    velocity->x = -HORIZONTAL_VELOICTY;
    right_facing=false;
}
void Player::update_position(Camera *game_cam)
{
    top_left->x += velocity->x;
    top_left->y += velocity->y-game_cam->velocity_y ;
    bottom_right->x += velocity->x;
    bottom_right->y += velocity->y -game_cam->velocity_y;
}
void Player::update_velocity(Camera *game_cam)
{
    velocity->x += acceleration->x;
    velocity->y += acceleration->y;
}
void Player::lose(Window *window)
{
    window->show_text(LOSE, Point(window->get_width() / 2-100, window->get_height() / 2), RED, FONT, 60);
    lost=true;
}
void Player::reflect(Window *window, Camera *game_cam)
{
    if (bottom_right->y > window->get_height())
    {
        lose(window);
    }
    if (window->get_width() < top_left->x)
    {
        top_left->x = 1;
        bottom_right->x = width;
    }
    if (bottom_right->x < 0)
    {
        top_left->x = window->get_width() - width;
        bottom_right->x = window->get_width();
    }
}

Player::Player(Velocity *velocity_, Acceleration *acceleration_, int width_, int height_, Velocity *previous_velocity_, Point *top_left_, Point *bottom_right_)

{
    velocity = velocity_;
    acceleration = acceleration_;
    top_left = top_left_;
    bottom_right = bottom_right_;
    bottom_right->x = top_left->x + width_;
    bottom_right->y = top_left->y + height_;
    width = width_;
    height = height_;
    previous_velocity = previous_velocity_;
    max_score = 0;
    last_max_score =max_score;
    right_facing=true;
    lost= false;
    jumping=true;
}
void Player::controls(Window *new_window)
{

    while (new_window->has_pending_event())
    {
        Event e = new_window->poll_for_event();
        switch (e.get_type())
        {
        case Event::EventType::QUIT:
            exit(0);
            break;
        case Event::EventType::MMOTION:

            break;
        case Event::KEY_PRESS:
            if (e.get_pressed_key() == D)
            {
                strafe_right();
            }
            if (e.get_pressed_key() == A)
            {
                strafe_left();
            }
        }
    }
}
