#pragma once
#include <raylib.h>
#include "scene.h"

class SceneManager
{

public:
    Scene* current_scene = nullptr;

    void handle_current_scene();
};