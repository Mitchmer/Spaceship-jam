#include "backgroundmanager.h"
#include <utility>


BackgroundManager::BackgroundManager(
        int gw, 
        int gh, 
        float scroll_spd, 
        std::vector<RandomAtlas> bgs
)   : game_width{gw}, game_height{gh}, scroll_speed{scroll_spd}, backgrounds{bgs}
{
    if (backgrounds.size() > 1)
        tail = backgrounds.size() - 1;
    for (RandomAtlas& atlas: backgrounds)
    {
        ++atlas;
    }
}

void BackgroundManager::add_background(RandomAtlas*& r_atlas)
{
    if (r_atlas != nullptr) 
    {
        ++(*r_atlas);
        backgrounds.push_back(std::move(*r_atlas));
        delete r_atlas;
        r_atlas = nullptr;
    }
}

void BackgroundManager::scroll_vertical() {
    // the BackgroundManager needs at least 3 elements in its vector in order to
    // function.
    // TECHNICALLY, this functionality will still work with only 2 elements, as long as the
    // "third_atlas" blocks below are removed; however, I kept the scrolling at three textures
    // at a time in case there are some frame artifacts with only two.
    if (backgrounds.size() > 2)
    {
        if (head == tail) 
        {
            head = 0;
            tail = backgrounds.size() - 1;
        }

        // define the "head" atlas, which will be the texture that initially fills the
        // screen and moves off (down) the screen
        RandomAtlas& head_atlas = backgrounds.at(head);

        // define the "next" atlas, which will be the texture that is drawn at a point
        // directly "above" the head atlas (a -y offset from the head). this will be
        // the texture that enters the screen as the head moves down the screen.
        // If the "next" index is greater than the vector size, then the "next" index chosen
        // is 0; this allows the vector to become a circular buffer.
        size_t next_index = head + 1;
        if (next_index >= backgrounds.size())
            next_index = 0;
        RandomAtlas& next_atlas = backgrounds.at(next_index);

        // define the "third" atlas, which will help provide the second atlas with a buffer,
        // and does the same job for the second atlas that the second atlas does for the
        // head.
        size_t third_index = next_index + 1;
        if (third_index >= backgrounds.size())
            third_index = 0;
        RandomAtlas& third_atlas = backgrounds.at(third_index);

        // Draw the head atlas such that it is centered on the screen. This is done by placing the upper-left
        // corner of the destination rectangle that DrawTexturePro() needs in the center of the screen; the texture
        // is then offset again by DrawTexturePro()'s origin parameter (back to the "intended" position of the
        // upper-left corner) in order to keep the origin of rotation and scaling in the middle of the texture.
        // The next atlas is drawn to "fill" an equivalent space above that, and then the third atlas is drawn 
        // to fill an equivalent space above the second.
        // Each texture is drawn at an offset defined by scroll_offset, which is incremented at a rate defined by
        // the scroll_speed variable.
        head_atlas.draw({game_width / 2.0f, ((float)game_height / 2.0f) + scroll_offset, (float)game_width, (float)game_height});
        next_atlas.draw({game_width / 2.0f, (-(float)game_height) + ((float)game_height / 2.0f) + scroll_offset, (float)game_width, (float)game_height});
        third_atlas.draw({game_width / 2.0f, (-(float)game_height * 2.0f) + ((float)game_height / 2.0f) + scroll_offset, (float)game_width, (float)game_height});
        
        scroll_offset += scroll_speed;

        // this will reset the scrolling offset once the "head" atlas' texture is completely off-screen, allowing
        // the "next" atlas to become the new head.
        // The previous "head" atlas is then set as the "tail," and is randomized to prepare for the next time it
        // appears on-screen.
        if (scroll_offset >= game_height) 
        {
            scroll_offset = 0.0f;
            tail = head;
            head = next_index;
            ++backgrounds.at(tail);
        }
    }
}

void BackgroundManager::set_scroll_speed(float speed)
{
    scroll_speed = speed;
}