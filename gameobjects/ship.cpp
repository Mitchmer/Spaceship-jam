#include "ship.h"

Ship::Ship(Atlas a, Vector2 pos, float scalar) 
    : atlas{a}
{
    hitbox = Rectangle(pos.x, pos.y, a.get_sprite_width() * scalar, a.get_sprite_height() * scalar);
    update_center();
}

void Ship::scale_ship_X(float scalar_x)
{
    hitbox.width *= scalar_x;
    update_center();
}

void Ship::scale_ship_Y(float scalar_y)
{
    hitbox.height *= scalar_y;
    update_center();
}

Rectangle Ship::get_hitbox() const 
{
    return hitbox;
}

Atlas Ship::get_atlas() const
{
    return atlas;
}

void Ship::change_sprite_direction(Ship::SpriteDirection sd)
{
    sprite_direction = sd;
    switch (sprite_direction)
    {
    case SpriteDirection::FORWARD:
        atlas.set_window_offset(0);
        break;
    case SpriteDirection::LEFT:
        atlas.set_window_offset(1);
        break;
    case SpriteDirection::RIGHT:
        atlas.set_window_offset(2);
        break;
    default:
        break;
    }
}

void Ship::incr_animation()
{
    ++atlas;
}

void Ship::draw_ship() const
{
    // atlas.draw({hitbox.x, hitbox.y, hitbox.width, hitbox.height});
    atlas.draw({center.x, center.y, hitbox.width, hitbox.height});
}

void Ship::set_ship_speed(Vector2 speed)
{
    ship_speed = speed;
}

void Ship::set_ship_direction(Vector2 direction)
{
    ship_direction = direction;
}

void Ship::set_ship_position(Vector2 position)
{
    hitbox.x = position.x;
    hitbox.y = position.y;
    update_center();
}

// diretional vector to move along
void Ship::move()
{
    hitbox.x += ship_direction.x * ship_speed.x;
    hitbox.y += ship_direction.y * ship_speed.y;
    update_center();
}

void Ship::update_center()
{
    center.x = hitbox.x + hitbox.width / 2.0f;
    center.y = hitbox.y + hitbox.height / 2.0f;
}