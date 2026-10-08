#pragma once
#include <raylib.h>
#include "../engine/atlas.h"

class MovableItem
{
protected:
    Atlas           atlas{};
    Rectangle       hitbox{};
    Vector2         center{};

    Vector2         direction{};
    Vector2         velocity{};
    Vector2         acceleration{};

public:
    MovableItem(
        Atlas atlas = Atlas{}, 
        Rectangle hitbox = Rectangle{});
  
    virtual void    move() = 0;
    virtual void    update_center() = 0;
    virtual void    draw() = 0;
    virtual void    print() = 0;
};