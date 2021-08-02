#ifndef _DOODLE_JUMP_HPP_
#define _DOODLE_JUMP_HPP_
#include "player.hpp"
#include "enemy.hpp"
#include "spring.hpp"
#include "platform.hpp"
#include <vector>
using namespace std;
class Gameplay
{
public:
    Player *player;
    Window *game_window;
    vector<Platform> platforms;
    vector<Enemy> enemies;
    vector<Spring> springs;
    Camera *game_cam;
    void draw_player();
    void init_platforms(vector<string> data);
    void init_springs(vector<string> data);
    void draw_spring();
    void cam_move_entities(int partition, int window_height);
    void spring_collision(double &jump_time);
    void init_enemy(vector<string> data);
    void enemy_collision();
    void score(int &max_height_climbed);
    void move_camera();
    void platform_collision(double jump_time);
    void moving_platforms();
    void draw_enemies();
    void draw_platforms();
    void draw_background();
    void jump_animation(double &jump_time);
    void render(int initial_velocity, int &max_height_climbed, double &jump_time);
    Gameplay(Window *new_window_, Player *player_, vector<Platform> platforms_, vector<string> data, Camera *game_cam_, vector<Enemy> enemies_, vector<Spring> springs_);
};
#endif