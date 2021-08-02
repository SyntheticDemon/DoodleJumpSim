using namespace std;
#include "headers.hpp"
#include "rsdl.hpp"
#include "DoodleJump.hpp"
#include "outerior_functions.hpp"
#define SCREEN_TITLE "Doodle Jump"
#define DELAY 18
void load_start()
{
    Window our_window = Window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    Window *new_window = &our_window;
    Point top_left = Point(our_window.get_width() / 2, our_window.get_width() / 2);
    Point bottom_right = Point(top_left.x + PLAYER_WIDTH, top_left.y + PLAYER_HEIGHT);
    Point top_left_copy = Point(top_left.x, top_left.y);
    Camera game_cam = Camera(ZERO, &top_left_copy);
    int initial_velocity = -JUMP_SPEED;
    int gravity = GRAVITY;
    vector<Platform> platforms;
    Velocity init_velocity = Velocity(ZERO, initial_velocity);
    Acceleration init_acceleration = Acceleration(ZERO, gravity);
    Velocity dummy_velocity = Velocity(0, 1);
    Player user = Player(&init_velocity, &init_acceleration, PLAYER_WIDTH, PLAYER_HEIGHT, &dummy_velocity, &top_left, &bottom_right);
    vector<Platform> platform;
    vector<string> data = read_file();
    vector<Enemy> enemies;
    vector<Spring> springs;
    int max_height_climbed = ZERO;
    double jump_time = 0;
    int boyant_velocity_y = user.velocity->y;
    Gameplay new_game = Gameplay(new_window, &user, platform, data, &game_cam, enemies, springs);
    while (true)
    {
        new_game.render(initial_velocity, max_height_climbed, jump_time);
        delay(DELAY);
    }

}
int main()
{
    load_start();
    return 0;
}
