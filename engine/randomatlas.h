#include "atlas.h"
#include <raylib.h>
#include <random>

class RandomAtlas : private Atlas
{
private:
    std::mt19937 gen; 
    std::uniform_int_distribution<int> distr_row;
    std::uniform_int_distribution<int> distr_col;
    std::uniform_int_distribution<int> distr_is_rotated_vertical;

    int         row_window_offset = 0;
    int         col_window_offset = 0;
    float       rotation = 0.0f;
    
    void        generate_random_window_offsets();

public:
    RandomAtlas(int sw = 0, int sh = 0, float anim_mult = 1.0f, Texture2D t = Texture2D{}, int num_columns = 1, int num_rows = 1);

    RandomAtlas operator++();

    void        draw(Rectangle destination) const;
    float       get_sprite_height() const;
    float       get_sprite_width() const;
    
};