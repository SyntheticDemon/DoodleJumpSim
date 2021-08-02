#ifndef _CAMERA_HPP_
#include "rsdl.hpp"
#define _CAMERA_HPP_
class Camera
{
public:
    int velocity_y;
    Point * coordinates;
    Camera(int velocity_y_, Point *coordinates_);
};
#endif