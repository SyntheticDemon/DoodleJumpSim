#include "DoodleJump.hpp"
#include "headers.hpp"
#include "outerior_functions.hpp"
#define OFFSET 20
#define LOSE_WIDTH 10
#define LOSE_OFFSET 50
#define JUMP_TIME 0.035
void Gameplay::Gameplay::draw_player()
{
    string ultimate;
    if (player->jumping && player->right_facing)
    {
        ultimate = RIGHT_JUMPING;
    }
    else if (player->jumping && player->right_facing == false)
    {
        ultimate = LEFT_JUMPING;
    }
    else if (player->jumping == false && player->right_facing == true)
    {
        ultimate = RIGHT;
    }
    else
    {
        ultimate = LEFT;
    }
    game_window->draw_img(ultimate, Rectangle(*player->top_left, *player->bottom_right));
}
void Gameplay::init_platforms(vector<string> data)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (i % 3 == 2)
        {
            if (data[i] == PLATFORM || data[i] == B_PLATFORM || data[i] == M_PLATFORM)
            {
                int velocity_x = 0;
                if (data[i] == M_PLATFORM)
                {
                    velocity_x = MOVING_PLAT_SPEED;
                }
                platforms.push_back(Platform(stoi(data[i - 2]) - PLAT_WIDTH / 2, -stoi(data[i - 1]) + game_window->get_height() - PLAT_HEIGHT, data[i], PLAT_WIDTH, PLAT_HEIGHT, velocity_x));
            }
        }
    }
}
void Gameplay::init_springs(vector<string> data)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == SPRING)
        {
            springs.push_back(Spring(stoi(data[i - 2]) - SPRING_WIDTH / 2, -stoi(data[i - 1]) - SPRING_HEIGHT + game_window->get_height(), false));
        }
    }
}
void Gameplay::draw_spring()
{
    for (int i = 0; i < springs.size(); i++)
    {
        Rectangle frame = Rectangle(Point(springs[i].x, springs[i].y), Point(springs[i].x + SPRING_WIDTH, springs[i].y + SPRUNG_HEIGHT));
        if (springs[i].sprung == true)
        {
            game_window->draw_img(SPRING_FILE, frame);
        }
        else
        {
            frame = Rectangle(Point(springs[i].x, springs[i].y), Point(springs[i].x + SPRING_WIDTH, springs[i].y + SPRING_HEIGHT));
            game_window->draw_img(SPRUNG_FILE, frame);
        }
    }
}
void Gameplay::cam_move_entities(int partition, int window_height)
{

    for (int i = 0; i < max(max(springs.size(), platforms.size()), enemies.size()); i++)
    {
        if (partition >= 50)
        {
            game_cam->velocity_y = -10;
            if (i < platforms.size())
                platforms[i].y += -game_cam->velocity_y;
            if (i < springs.size())
                springs[i].y += -game_cam->velocity_y;
            if (i < enemies.size())
                enemies[i].y += -game_cam->velocity_y;
        }
        else
        {
            game_cam->velocity_y = ZERO;
        }
    }
}
void Gameplay::spring_collision(double &jump_time)
{
    for (int i = 0; i < springs.size(); i++)
    {
        int height_difference = distance_calculator(Point(player->top_left->x, springs[i].y), *player->top_left);
        int x_difference = distance_calculator(Point(springs[i].x, player->top_left->y), *player->top_left);
        if (player->velocity->y > 0)
        {
            SDL_Rect platform_box = {springs[i].x, springs[i].y, SPRING_HEIGHT, SPRING_WIDTH};
            SDL_Rect player_box = {player->top_left->x, player->top_left->y, PLAYER_WIDTH, PLAYER_HEIGHT};
            SDL_Rect result;
            if (SDL_IntersectRect(&platform_box, &player_box, &result) == true && player->bottom_right->y < springs[i].y +SPRING_HEIGHT)
            {
                player->velocity->y = -SPRING_JUMP_SPEED;
                player->velocity->x = ZERO;
                player->jumping = true;
                springs[i].sprung=true;
                jump_time = clock();
            }
        }
    }
}
void Gameplay::init_enemy(vector<string> data)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == ENEMY)
        {
            enemies.push_back(Enemy(stoi(data[i - 2]) - ENEMY_WIDTH / 2, -stoi(data[i - 1]) + game_window->get_height() - ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT));
        }
    }
}
void Gameplay::enemy_collision()
{
    for (int i = 0; i < enemies.size(); i++)
    {

        int height_difference = distance_calculator(Point(player->top_left->x, enemies[i].y), *player->top_left);
        int x_difference = distance_calculator(Point(enemies[i].x, player->top_left->y), *player->top_left);
        if (height_difference < ENEMY_HEIGHT && x_difference < enemies[i].width - OFFSET)
        {
            player->lose(game_window);
        }
    }
}

void Gameplay::score(int &max_height_climbed)
{

    Point start = Point(game_window->get_width() / 2, game_window->get_height() / 2 - game_cam->coordinates->y);
    Point player_bottom = Point(game_window->get_width() / 2, player->bottom_right->y);
    float current = game_window->get_height() / 2 + distance_calculator(start, player_bottom);
    if (current >= max_height_climbed && player->lost == false)
    {
        max_height_climbed = current;
    }
    game_window->show_text(to_string(int(max_height_climbed)), Point(game_window->get_width() - LOSE_OFFSET, LOSE_WIDTH), BLACK, GAME_FONT);
}
void Gameplay::move_camera()
{
    int window_height = game_window->get_height();
    float velocity_accurate = player->velocity->y;
    int partition = window_height / 2 - remainder(player->bottom_right->y, window_height / 2);
    if (player->bottom_right->y < window_height / 2)
    {
        cam_move_entities(partition, window_height);
        game_cam->coordinates->y += game_cam->velocity_y;
    }
}
void Gameplay::platform_collision(double jump_time)
{
    for (int i = 0; i < platforms.size(); i++)
    {
        if (player->velocity->y > ZERO)
        {

            if (platforms[i].type != B_PLATFORM)
            {
                SDL_Rect platform_box = {platforms[i].x, platforms[i].y, PLAT_WIDTH, PLAT_HEIGHT};
                SDL_Rect player_box = {player->top_left->x, player->top_left->y, PLAYER_WIDTH, PLAYER_HEIGHT};
                SDL_Rect result;
                if (SDL_IntersectRect(&platform_box, &player_box, &result) == true && player->bottom_right->y < platforms[i].y + platforms[i].height)
                {
                    player->velocity->y = -JUMP_SPEED;
                    player->velocity->x = ZERO;
                    player->jumping = true;
                    jump_time = clock();
                }
            }
        }
    }
}
void Gameplay::moving_platforms()
{
    for (int i = 0; i < platforms.size(); i++)
    {
        if (platforms[i].type == M_PLATFORM)
        {
            platforms[i].x += platforms[i].velocity_x;
            if (platforms[i].x + platforms[i].width > game_window->get_width() || platforms[i].x < 0)
            {
                platforms[i].velocity_x = -platforms[i].velocity_x;
            }
        }
    }
}
void Gameplay::draw_enemies()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        Rectangle frame = Rectangle(Point(enemies[i].x, enemies[i].y), Point(enemies[i].x + ENEMY_WIDTH, enemies[i].y + ENEMY_HEIGHT));
        game_window->draw_img(ENEMY_FILE, frame);
    }
}
void Gameplay::draw_platforms()
{

    for (int i = 0; i < platforms.size(); i++)
    {
        Rectangle frame = Rectangle(Point(platforms[i].x, platforms[i].y), Point(platforms[i].x + PLAT_WIDTH, platforms[i].y + PLAT_HEIGHT));

        if (platforms[i].type == PLATFORM)
        {
            game_window->draw_img(GREEN_PLATFORM, frame);
        }
        else if (platforms[i].type == B_PLATFORM)
        {
            game_window->draw_img(BROKEN_PLATFORM, frame);
        }
        else if (platforms[i].type == M_PLATFORM)
        {
            game_window->draw_img(MOVING_PLATFORM, frame);
        }
    }
}
void Gameplay::draw_background()
{
    game_window->draw_img(BACKGROUND, Rectangle(Point(ZERO, ZERO), Point(game_window->get_width(), game_window->get_height())));
}
void Gameplay::jump_animation(double &jump_time)
{
    if ((clock() - jump_time) / CLOCKS_PER_SEC > JUMP_TIME)
    {
        player->jumping = false;
        jump_time = clock();
    }
}
void Gameplay::render(int initial_velocity, int &max_height_climbed, double &jump_time)
{
    game_window->clear();
    player->controls(game_window);
    if (player->lost == true)

    {
        score(max_height_climbed);
        draw_background();
        player->lose(game_window);
    }
    else
    {
        move_camera();
        game_window->clear();
        draw_background();
        player->update_velocity(game_cam);
        player->update_position(game_cam);
        player->reflect(game_window, game_cam);
        draw_platforms();
        platform_collision(jump_time);
        moving_platforms();
        enemy_collision();
        draw_enemies();
        draw_spring();
        score(max_height_climbed);
        jump_animation(jump_time);
        spring_collision(jump_time);
        draw_player();
    }
    game_window->update_screen();
}
Gameplay::Gameplay(Window *new_window_, Player *player_, vector<Platform> platforms_, vector<string> data, Camera *game_cam_, vector<Enemy> enemies_, vector<Spring> springs_)
{
    game_window = new_window_;
    player = player_;
    platforms = platforms_;
    init_platforms(data);
    enemies = enemies_;
    init_enemy(data);
    game_cam = game_cam_;
    springs = springs_;
    init_springs(data);
}