#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_
#include <string>
class Platform
{
public:
    int x;
    int y;
    int width;
    int height;
    int velocity_x;
    std::string type;
    Platform(int x_, int y_, std ::string type_, int width_, int height_,int velocity_x_);
};
#endif