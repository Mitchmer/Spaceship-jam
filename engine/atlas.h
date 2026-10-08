#pragma once
#include <raylib.h>
#include <raymath.h>
#include <string>

class Atlas {
protected:
    int         sprite_width{0};
    int         sprite_height{0};
    Texture2D   texture{};

    int         num_frames{0};
    int         current_frame{0};

    float       animation_multiplier{1.0f};
    float       frame_speed{0};
    float       frame_counter{0};
    
    Rectangle   window{};
    int         window_offset{0};

public:
    Atlas(int sw = 0, int sh = 0, float anim_mult = 1.0f, Texture2D t = Texture2D{});
    Atlas(int sw, int sh, float anim_mult, std::string fn);
    
    Atlas       operator++();
    Atlas       operator++(int);

    int         get_num_frames() const;
    float       get_frame_speed() const;
    void        set_animation_multiplier(float mult);
    void        set_window_offset(int offset);
    void        reset();
    bool        is_last_frame() const;

    float       get_sprite_height() const;
    float       get_sprite_width() const;
    void        draw(Rectangle destination, float rotation = 0.0f, Color tint = WHITE) const;

};