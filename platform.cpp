#include "platform.hpp"
#include <string>
Platform::Platform(int x_, int y_, std ::string type_, int width_, int height_,int velocity_x_)
{
    x = x_;
    y = y_;
    type = type_;
    velocity_x=velocity_x_;
    width = width_;
    height = height_;
}