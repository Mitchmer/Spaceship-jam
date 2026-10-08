#include "junkmanager.h"
#include <utility>

JunkManager::JunkManager(
        std::vector<Junk> active_junk, 
        std::vector<Junk> available_junk,
        int max_junk,
        Rectangle game_bounds,
        float max_rotation_speed,
        float max_object_scalar
    )
: active_junk{active_junk}, available_junk{available_junk}, max_junk{max_junk}, game_bounds{game_bounds}
{
    std::random_device rd;
    gen = std::mt19937(rd());

    // random x position
    distr_x_position = std::uniform_real_distribution<float>(game_bounds.x, game_bounds.x + game_bounds.width);
    // random x direction
    // random rotation
    distr_rotation = std::uniform_real_distribution<float>(0, 360.0f);
    // random rotation speed
    distr_max_rotation_speed = std::uniform_real_distribution<float>(-max_rotation_speed, max_rotation_speed);
    // random object scalar
    distr_max_object_scalar = std::uniform_real_distribution<float>(1.0f, max_object_scalar);
}   

void JunkManager::add_junk(Junk junk)
{
    junk.set_direction_speed(junk_speed);
    available_junk.push_back(junk);
}

void JunkManager::spawn_junk()
{
    if ((max_junk > 0) && (active_junk.size() < max_junk) && (!available_junk.empty()))
    {
        // get the following random values:
        // random index
        distr_junk_index = std::uniform_int_distribution<int>(0, (available_junk.size() - 1));
        int index = distr_junk_index(gen);
        // random x position
        float x_pos = distr_x_position(gen);
        // random x direction
        // random rotation
        float rot = distr_rotation(gen);
        // random rotation speed
        float rot_speed = distr_max_rotation_speed(gen);
        // random object scalar
        float scalar = distr_max_object_scalar(gen);

        Junk new_junk = available_junk.at(index);
        available_junk.erase(available_junk.begin() + index);

        new_junk.set_hitbox(
            Rectangle{
                x_pos, 
                0.0f - new_junk.get_atlas().get_sprite_height() * scalar, // spawn it well above the upper game window boundary
                new_junk.get_atlas().get_sprite_width() * scalar, 
                new_junk.get_atlas().get_sprite_height() * scalar
            });
        new_junk.set_rotation(rot);
        new_junk.set_rotation_speed(rot_speed);

        active_junk.push_back(new_junk);
    }
}

size_t JunkManager::get_max_junk() const
{
    return max_junk;
}

void JunkManager::set_junk_speed(Vector2 speed)
{
    junk_speed = speed;
}
void JunkManager::set_junk_breaking_dir_speed(Vector2 speed)
{
    junk_breaking_dir_speed = speed;
}

void JunkManager::draw_active_junk() 
{
    for (std::vector<Junk>::iterator it = active_junk.begin(); it != active_junk.end();)
    {
        Junk& junk = *it;

        junk.draw();
        junk.move();
        if (junk.get_hitbox().y - (junk.get_hitbox().height * 2.0f) > game_bounds.height) // once it's well below the lower game window boundary
        {
            junk.remove_destruction();
            available_junk.push_back(junk);
            it = active_junk.erase(it);
            continue;
        } else if (junk.get_is_breaking())
        {
            if (junk.check_frame_delta())
            {
                junk.inc_break_state();
                junk.reset_frame_counter();
            } 
            else
            {
                junk.incr_frame_counter();
            }
            if (junk.get_atlas().is_last_frame())
            {
                junk.remove_destruction();
                junk.set_direction_speed(junk_speed);
                available_junk.push_back(junk);
                it = active_junk.erase(it);
                continue;
            }
        }
        ++it;
    }
}
void JunkManager::check_collisions(const Ship& ship, bool debug)
{
    if (debug)
        DrawRectangleLines(ship.get_hitbox().x, ship.get_hitbox().y, ship.get_hitbox().width, ship.get_hitbox().height, GREEN);
    for (Junk& junk: active_junk)
    {
        if (debug)
            DrawRectangleLines(junk.get_hitbox().x, junk.get_hitbox().y, junk.get_hitbox().width, junk.get_hitbox().height, BLUE);
        if(!(junk.get_is_breaking()) && CheckCollisionRecs(ship.get_hitbox(), junk.get_hitbox()))
        {
            junk.toggle_is_breaking();
            junk.set_direction_speed({0.0f, 2.5f});
        }
    }
}
