#include "randomatlas.h"
#include <iostream>

RandomAtlas::RandomAtlas(int sw, int sh, float anim_mult, Texture2D t, int cols, int rows)
    : Atlas{sw, sh, anim_mult, t}
{
    std::random_device rd;
    gen = std::mt19937(rd());
    distr_row = std::uniform_int_distribution<int>(0, rows - 1);
    distr_col = std::uniform_int_distribution<int>(0, cols - 1);
    distr_is_rotated_vertical = std::uniform_int_distribution<int>(0,1);

    generate_random_window_offsets();
}

RandomAtlas RandomAtlas::operator++() 
{
    generate_random_window_offsets();
    window.x = sprite_width * col_window_offset;
    window.y = sprite_height * row_window_offset;
    return *this;
}

void RandomAtlas::generate_random_window_offsets()
{
    row_window_offset = distr_row(gen);
    col_window_offset = distr_col(gen);
    if((bool)distr_is_rotated_vertical(gen))
        rotation = -180.0f;
    else
        rotation = 0.0f;
}

float RandomAtlas::get_sprite_height() const { return Atlas::get_sprite_height(); }
float RandomAtlas::get_sprite_width() const { return Atlas::get_sprite_width(); }

// because the origin will offset the "destination" rectangle, for 
// textures that need collision checking, it may be beneficial to pass
// the center coordinates of the object's hitbox as "destination"'s x,y coordinates
// and then set the origin as the center of this new rectangle; the two
// offsets will effectively cancel each other out, while keeping the origin where the
// center is and the texture where the object's hitbox is
void RandomAtlas::draw(Rectangle destination) const 
{
    DrawTexturePro(texture, window, destination, {destination.width / 2.0f, destination.height / 2.0f}, rotation, WHITE);
}
