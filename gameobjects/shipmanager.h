#pragma once
#include <raylib.h>
#include "ship.h"

class ShipManager  
{
private:
    Ship* current_ship = nullptr;
    Vector2 upper_game_boundary = {0.0f, 0.0f};
    Vector2 lower_game_boundary = {0.0f, 0.0f};
    float ship_frame_counter{0};

public:
    ShipManager(Ship* ship, Vector2 upper_game_boundary, Vector2 lower_game_boundary);
    void enforce_ship_position();
    void set_ship_direction();
    void update_animation();
};