#pragma once
#include <raylib.h>
#include "randomatlas.h"
#include <random>
#include <vector>

class BackgroundManager
{
private:
    std::vector<RandomAtlas> backgrounds{};

    int game_width{32};
    int game_height{32};
    float scroll_speed{0.0f};
    size_t head{1};
    size_t tail{0};
    float scroll_offset{0.0f};

public:
    BackgroundManager(
        int game_width = 32.0f, 
        int game_height = 32.0f, 
        float scroll_speed = 1.0f, 
        std::vector<RandomAtlas> backgrounds = std::vector<RandomAtlas>{}
    );
    void add_background(RandomAtlas*& r_atlas);
    void scroll_vertical();
    void set_scroll_speed(float speed);
};