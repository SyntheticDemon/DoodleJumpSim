#ifndef _HEADER_HPP_
#define _HEADER_HPP_
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <random>
#include "rsdl.hpp"
#include "velocity.hpp"
#include "acceleration.hpp"
#include "player.hpp"
#include "camera.hpp"
#include "platform.hpp"
#include "enemy.hpp"
#include <cmath>
#define GRAVITY 1
#define MIN_RANGE 80
#define PLAT_WIDTH 80
#define ENEMY_HEIGHT 92
#define ENEMY_WIDTH 74
#define PLAT_HEIGHT 20
#define PLAYER_HEIGHT 90
#define PLAYER_WIDTH 90
#define SPRING_WIDTH 30
#define SPRING_HEIGHT 30
#define JUMP_SPEED 25
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 1024 
#define SPRING_JUMP_SPEED 40
#define MOVING_PLAT_SPEED 3
#define ZERO 0
#define SPRUNG_HEIGHT 50
#define SPRING "spring"
#define GAME_FONT "assets/gamefont.ttf"
#define SPRING_FILE "assets/spring.png"
#define GREEN_PLATFORM "assets/greenplatform.png"
#define BROKEN_PLATFORM "assets/bplatform.png"
#define SPRUNG_FILE "assets/sprung.png"
#define MOVING_PLATFORM "assets/mplatform.png"
#define RIGHT "assets/right.png"
#define RIGHT_JUMPING  "assets/right_jumping.png"
#define LEFT_JUMPING  "assets/left_jumping.png"
#define LEFT "assets/left.png"
#define B_PLATFORM "bplatform"
#define M_PLATFORM "mplatform"
#define PLATFORM "platform"
#define ENEMY "enemy"
#define ENEMY_FILE "assets/enemy.png"
#define INPUT_FILE "map.txt"
#define BACKGROUND "assets/background.png"
#endif