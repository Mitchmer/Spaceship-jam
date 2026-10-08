#pragma once
#include <raylib.h>

class Scene
{
public:
    bool is_active{false};
    virtual void handle_scene() = 0;
};