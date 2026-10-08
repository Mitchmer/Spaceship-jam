#pragma once
#include "../engine/atlas.h"
#include <raylib.h>

class Ship {
public:

    enum class SpriteDirection {
        FORWARD,
        LEFT,
        RIGHT
    };

private:
    Atlas atlas{};
    Rectangle hitbox{0,0,0,0};
    Vector2 center{0,0};
    SpriteDirection sprite_direction{SpriteDirection::FORWARD};

    Vector2 ship_direction{0.0f, 0.0f};
    Vector2 ship_speed{0.0f, 0.0f};

public:

    Ship(Atlas atlas, Vector2 position = {0.0f,0.0f}, float scalar = 1.0f);

    void scale_ship_X(float scalar_x);
    void scale_ship_Y(float scalar_y);
    Rectangle get_hitbox() const;

    Atlas get_atlas() const;
    void change_sprite_direction(Ship::SpriteDirection sprite_direction);
    void incr_animation();
    void draw_ship() const;

    void set_ship_speed(Vector2 speed);
    void set_ship_direction(Vector2 direction);
    void set_ship_position(Vector2 position);
    void move();

private:
    void update_center();
};