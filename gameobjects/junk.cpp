#include "junk.h"
#include <raymath.h>
#include <iostream>

Junk::Junk(
    Atlas atlas, 
    Rectangle hitbox, 
    bool is_destructible,
    Vector2 direction_normal,
    Vector2 direction_speed,
    float rotation,
    float rotation_speed) 
: MovableItem{atlas, hitbox}
{
    this->is_destructible = is_destructible;
    this->direction_normal = direction_normal;
    this->direction_speed = direction_speed;
    this->rotation = rotation;
    this->rotation_speed = rotation_speed;

}

void Junk::set_hitbox(Rectangle hitbox) 
{ 
    this->hitbox = hitbox; 
    update_center();
}
void Junk::set_rotation(float rotation) { this->rotation = rotation; }
void Junk::set_rotation_speed(float rotation_speed) { this->rotation_speed = rotation_speed; }
void Junk::set_direction_speed(Vector2 direction_speed) { this->direction_speed = direction_speed; }
void Junk::toggle_is_breaking() { is_breaking = !is_breaking; }

void Junk::inc_break_state() {
    ++atlas;
}

void Junk::remove_destruction() {
    if (is_destructible)
    {
        atlas.reset();
        if (is_breaking)
            is_breaking = false;
    }
    
}

bool Junk::check_frame_delta()
{
    return frame_counter >= atlas.get_frame_speed();
}

void Junk::incr_frame_counter()
{
    ++frame_counter;
}

void Junk::reset_frame_counter()
{
    frame_counter = 0.0f;
}


Atlas Junk::get_atlas() const { return atlas; }
bool Junk::get_is_destructible() const { return is_destructible; }
bool Junk::get_is_breaking() const { return is_breaking; }
Rectangle Junk::get_hitbox() const { return hitbox; }

void Junk::move()
{
    Vector2 new_pos
    {
        Vector2Add(
            {hitbox.x,hitbox.y}, 
            Vector2Multiply(direction_normal, direction_speed))
    };
    hitbox.x = new_pos.x;
    hitbox.y = new_pos.y;
    rotation += rotation_speed;
    if (rotation >= 360.0f)
    {
        rotation += -360.0f;
    }
    if (rotation <= -360.0f)
    {
        rotation += 360.0f;
    }
    update_center();
}

void Junk::update_center()
{
    center = Vector2{hitbox.x + (hitbox.width / 2.0f), hitbox.y + (hitbox.height / 2.0f)};
}

void Junk::draw()
{
    atlas.draw(Rectangle{center.x, center.y, hitbox.width, hitbox.height}, rotation);
}

void Junk::print() 
{
    std::cout << "===== Hitbox ======" << std::endl
              << "x: \t" << hitbox.x << std::endl
              << "y: \t" << hitbox.y << std::endl
              << "width: \t" << hitbox.width << std::endl
              << "height: " << hitbox.height << std::endl;
}