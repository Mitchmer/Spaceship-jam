#pragma once
#include <raylib.h>
#include "movableitem.h"
#include "../engine/atlas.h"
#include "../engine/destructible.h"

class Junk : public MovableItem //, Destructible
{

private:
    Vector2     direction_normal{};
    Vector2     direction_speed{};
    float       rotation{0.0f};
    float       rotation_speed{0.0f};
    bool        is_destructible{false};
    float       frame_counter{0};
    bool is_breaking{false};

public:
    Junk(
        Atlas       atlas = {}, 
        Rectangle   hitbox = Rectangle{},
        bool        is_destructible = false,
        Vector2     direction_normal = Vector2{}, 
        Vector2     direction_speed = Vector2{},
        float       rotation = 0.0f,
        float       rotation_speed = 0.0f
    );

    void        set_hitbox(Rectangle hitbox);
    void        set_rotation(float rotation);
    void        set_rotation_speed(float rotation_speed);
    void        set_direction_speed(Vector2 direction_speed);
    void        toggle_is_breaking();
    void        inc_break_state();
    bool        check_frame_delta();
    void        incr_frame_counter();
    void        reset_frame_counter();
    void        remove_destruction();

    Atlas       get_atlas() const;
    bool        get_is_destructible() const;
    bool        get_is_breaking() const;
    Rectangle   get_hitbox() const;

    void        move() override;
    void        update_center() override;
    void        draw() override;
    void        print() override;
};