#pragma once

#include <raylib.h>
#include "../engine/backgroundmanager.h"
#include "../gameobjects/junkmanager.h"
#include "../engine/scenemanager.h"

class Application
{
public:
    static Application* instance();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    bool init(int argc, char** argv);
    int run(int argc, char** argv);
    void shutdown();

    static Vector2 upper_game_boundary;
    static Vector2 lower_game_boundary;
    static SceneManager scene_manager;
    static BackgroundManager background_manager;
    static JunkManager junk_manager;
    static bool debug;


private:
    Application() = default;
    ~Application();

    static constexpr int kWindowWidth = 1600;
    static constexpr int kWindowHeight = 900;
    static constexpr int kFPS = 60;
    static constexpr int kGameBoundaryMarginX = 20;
    static constexpr int kGameBoundaryMarginY = 20;
    static constexpr float animation_mult = 0.5f;

    bool _initialized = false;

public:
    KeyboardKey get_keyboard_input();
};
