#include "atlas.h"

// create atlas from pre-loaded texture
Atlas::Atlas(int sw, int sh, float anim_mult, Texture2D t)
    : sprite_width{sw}, sprite_height{sh}, texture{t}, animation_multiplier{anim_mult}
{
    // divide texture2D width by sprite_width to get # of "frames"
    if (sprite_width == 0)
        num_frames = 0;
    else
        num_frames = texture.width / sprite_width;

    if (animation_multiplier == 0)
        frame_speed = 1.0f;
    else
        frame_speed = (float)num_frames / animation_multiplier;
    
    window = Rectangle{0, 0, (float)sprite_width, (float)sprite_height};
}

// create Atlas by loading a texture from the given filename
Atlas::Atlas(int sw, int sh, float anim_mult, std::string fn)
    : Atlas(sw, sh, anim_mult, LoadTexture(fn.c_str())) {}

// prefix increment
// moves the "window" horizontally across the sprite sheet to the next 
// "frame" of the sprite animation
Atlas Atlas::operator++()
{
    ++current_frame;
    if (current_frame >= num_frames)
        current_frame = 0;
    window.x = (float)(sprite_width * current_frame);
    window.y = window.height * (float)window_offset;
    return *this;
}

// postfix increment
// moves the "window" horizontally across the sprite sheet to the next 
// "frame" of the sprite animation
Atlas Atlas::operator++(int)
{
    Atlas temp = *this;
    ++current_frame;
    if (current_frame >= num_frames)
        current_frame = 0;
    window.x = (float)(sprite_width * current_frame);
    window.y = window.height * (float)window_offset;
    return temp;
}

// return the number of frames to complete an animation
int Atlas::get_num_frames() const 
{
    return num_frames;
}

float Atlas::get_frame_speed() const 
{
    return frame_speed;
}

void Atlas::set_animation_multiplier(float mult)
{
    animation_multiplier = mult;
    frame_speed = num_frames / animation_multiplier;
}

// the vertical scalar offset from the upper right corner of 
// the sprite sheet, such that an increase in window_offset
// will move the window (of what sprite animation is currently
// being viewed) to a different "row" of the sprite sheet.
void Atlas::set_window_offset(int offset) 
{
    window_offset = offset;
    window.x = (float)(sprite_width * current_frame);
    window.y = window.height * (float)window_offset;
}

void Atlas::reset() {
    current_frame = 0;
    set_window_offset(0);
}

bool Atlas::is_last_frame() const { 
    return (current_frame + 1) >= num_frames; 
}

float Atlas::get_sprite_height() const { return sprite_height; }
float Atlas::get_sprite_width() const { return sprite_width; }

// because the origin will offset the "destination" rectangle, for 
// textures that need collision checking, it may be beneficial to pass
// the center coordinates of the object's hitbox as "destination"'s x,y coordinates
// and then set the origin as the center of this new rectangle; the two
// offsets will effectively cancel each other out, while keeping the origin where the
// center is and the texture where the object's hitbox is
void Atlas::draw(Rectangle destination, float rotation, Color tint) const 
{
    DrawTexturePro(texture, window, destination, {destination.width / 2.0f, destination.height / 2.0f}, rotation, tint);
}