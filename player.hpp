#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include "player.hpp"
#include "rsdl.hpp"
#include "acceleration.hpp"
#include "velocity.hpp"
#include "camera.hpp"
class Player
{
public:
    Velocity *velocity;
    Acceleration *acceleration;
    Point *position;
    int width;
    int height;
    int last_max_score;
    int max_score;
    bool right_facing;
    bool lost;
    bool jumping;
    Velocity *previous_velocity;
    void update_position(Camera *game_cam);
    void strafe_right();
    void strafe_left();
    void update_velocity(Camera *game_cam);
    void reflect(Window *window, Camera *game_cam);
    void controls(Window *window);
    void lose(Window *window);
    Point *top_left;
    Point *bottom_right;
    Player(Velocity *velocity_, Acceleration *acceleration_, int width_, int height_, Velocity *previous_velocity, Point *top_left_, Point *bottom_right_);
};
#endif
