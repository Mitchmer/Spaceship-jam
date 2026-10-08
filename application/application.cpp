#include "application.h"
#include <iostream>
#include "../gameobjects/ship.h"
#include "../gameobjects/shipmanager.h"
#include "../engine/atlas.h"
#include "../gameobjects/junk.h"
#include "../engine/startscene.h"

SceneManager Application::scene_manager = SceneManager{};
Vector2 Application::upper_game_boundary = Vector2(0 , 0); 
Vector2 Application::lower_game_boundary = Vector2(kWindowWidth, kWindowHeight);
BackgroundManager Application::background_manager = BackgroundManager{kWindowWidth, kWindowHeight, 5.0f};
JunkManager Application::junk_manager = JunkManager{
    std::vector<Junk>(),
    std::vector<Junk>(),
    500,
    Rectangle{0, 0, kWindowWidth, kWindowHeight},
    10.0f,
    2.5f
};
bool Application::debug = false;

Application* Application::instance()
{
    static Application app;
    return &app;
}

Application::~Application()
{
    shutdown();
}

bool Application::init(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    if (_initialized)
    {
        return true;
    }

    InitWindow(kWindowWidth, kWindowHeight, "Raylib Minimal Template");
    SetTargetFPS(kFPS);

    scene_manager.current_scene = new StartScene{kWindowWidth, kWindowHeight};
    scene_manager.current_scene->is_active = true;

    junk_manager.set_junk_speed(Vector2{0.0f, 10.0f});
    junk_manager.set_junk_breaking_dir_speed(Vector2{0.0f, 2.5f});
    Texture2D asteroid_texture = LoadTexture("../../assets/breakable_asteroid.png");
    for (size_t i {0}; i < junk_manager.get_max_junk(); ++i)
    {
        Atlas atlas = Atlas{64, 64, 1.0f, asteroid_texture};
        junk_manager.add_junk(Junk{
            atlas, 
            Rectangle{0, 0, 32.0f, 32.0f}, 
            true,
            Vector2{0.0f, 1.0f}
        });
    }

    // Add 3 background randomized atlases to the background manager
    for (int i{0}; i < 3; ++i) 
    {
        RandomAtlas* main_background = new RandomAtlas{256, 144, 0.0f, LoadTexture("../../assets/main_star_background.png"), 2, 4};
        background_manager.add_background(main_background);
    }

    upper_game_boundary = Vector2{kGameBoundaryMarginX, kGameBoundaryMarginY};
    lower_game_boundary = Vector2{kWindowWidth - kGameBoundaryMarginX, kWindowHeight - kGameBoundaryMarginY};

    _initialized = true;
    return true;
}

int Application::run(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    float scalar = 10.0f;
    
    // Set up player ship
    Atlas shipAtlas{22, 32, animation_mult, "../../assets/ship_01.png"};
    Ship ship{shipAtlas};
    ship.scale_ship_X(4.0f);
    ship.scale_ship_Y(4.0f);
    ship.set_ship_speed({5.0f, 0.0f});
    ship.set_ship_position({(float)kWindowWidth / 2.0f, lower_game_boundary.y - ship.get_hitbox().height});

    ShipManager ship_manager{&ship, upper_game_boundary, lower_game_boundary};

    if (!_initialized && !init(argc, argv))
    {
        return -1;
    }

    float delta_time = GetFrameTime();

    while (!WindowShouldClose())
    {
        Scene* current_scene = scene_manager.current_scene;

        BeginDrawing();
        //main_background;
        background_manager.scroll_vertical();

        if (StartScene* scene = dynamic_cast<StartScene*>(current_scene))
        {
            if (scene->is_active)
            {
                scene->handle_scene();
            }
            else
            {
                scene_manager.current_scene = nullptr;
            }
        }
        else 
        {        
            delta_time += GetFrameTime();
            if (delta_time >= 0.0025f)
            {
                junk_manager.spawn_junk();
                delta_time = 0.0f;
            }
            
            junk_manager.check_collisions(ship, debug);
            junk_manager.draw_active_junk();

            ship_manager.set_ship_direction();
            ship.move();
            ship_manager.enforce_ship_position();
            ship.draw_ship();
            

            ship_manager.update_animation();
        }




        ClearBackground(Color{24, 28, 36, 255});
        EndDrawing();

    }

    shutdown();
    return 0;
}

void Application::shutdown()
{
    if (_initialized)
    {
        CloseWindow();
        _initialized = false;
    }
}
