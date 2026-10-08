#include "startscene.h"

StartScene::StartScene(int game_width, int game_height)
    : game_width{game_width}, game_height{game_height} 
{
    gen = std::mt19937{};
    distr_color = std::uniform_int_distribution<int>(0,255);
}

void StartScene::handle_scene()
    {
        if(IsKeyDown(KEY_SPACE))
        {
            is_active = false;
        }
        else
        {
            frame_time += GetFrameTime();
            if (frame_time >= 0.5f)
            {
                update_start_text();
                frame_time = 0.0f;
            }
            DrawText("Press SPACE to Start",(float)game_width / 2.0f - 100, (float)game_height / 2.0f, 48, start_text_color);
        }
    }

void StartScene::update_start_text()
{
    frame_time += GetFrameTime();
    if (frame_time >= start_text_color_speed)
    {
        start_text_color = Color{(unsigned char)distr_color(gen),(unsigned char)distr_color(gen),(unsigned char)distr_color(gen),(unsigned char)distr_color(gen)};
        frame_time = 0.0f;
    }
}