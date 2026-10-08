#pragma once
#include "scene.h"
#include <random>

class StartScene : public Scene
{
private:
    float frame_time{0.0f};
    std::mt19937 gen;
    std::uniform_int_distribution<int> distr_color;
    int game_width{100};
    int game_height{100};

public:
    StartScene(int game_width, int game_height);
    float start_text_color_speed{0.0f};
    Color start_text_color{WHITE};

    void handle_scene() override;
    void update_start_text();
};