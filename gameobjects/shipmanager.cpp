#include "shipmanager.h"
#include <iostream>

ShipManager::ShipManager(Ship* ship, Vector2 upper, Vector2 lower)
    : current_ship{ship}, upper_game_boundary{upper}, lower_game_boundary{lower} {}

void ShipManager::enforce_ship_position() 
{
    Rectangle ship_hitbox = current_ship->get_hitbox();
    bool isOOB = false;

    if (ship_hitbox.x < upper_game_boundary.x)
        current_ship->set_ship_position({upper_game_boundary.x, ship_hitbox.y});
    else if (ship_hitbox.x > lower_game_boundary.x - ship_hitbox.width)
        current_ship->set_ship_position({lower_game_boundary.x - ship_hitbox.width, ship_hitbox.y});

    if (ship_hitbox.y < upper_game_boundary.y)
        current_ship->set_ship_position({ship_hitbox.x, upper_game_boundary.y});
    else if (ship_hitbox.y > lower_game_boundary.y - ship_hitbox.height)
        current_ship->set_ship_position({ship_hitbox.x, lower_game_boundary.y - ship_hitbox.height});
}

void ShipManager::set_ship_direction() 
{
    if (IsKeyDown(KEY_A))
    {
        current_ship->change_sprite_direction(Ship::SpriteDirection::LEFT);
        current_ship->set_ship_direction(Vector2{-1.0f, 0.0f});
    }
    else if (IsKeyDown(KEY_D))
    {
        current_ship->change_sprite_direction(Ship::SpriteDirection::RIGHT);
        current_ship->set_ship_direction(Vector2{1.0f, 0.0f});
    }
    else
    {
        current_ship->change_sprite_direction(Ship::SpriteDirection::FORWARD);
        current_ship->set_ship_direction(Vector2{0.0f, 0.0f});
    }
}

void ShipManager::update_animation() 
{   
    if ((++ship_frame_counter) >= current_ship->get_atlas().get_frame_speed())
    {
        ship_frame_counter = 0;
        current_ship->incr_animation();
    }
}