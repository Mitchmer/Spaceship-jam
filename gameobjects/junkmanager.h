#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <random>
#include "ship.h"
#include "junk.h"

class JunkManager 
{
private:
    std::vector<Junk> active_junk{};
    std::vector<Junk> available_junk{};
    int max_junk{0};
    Rectangle game_bounds{};

    std::mt19937 gen; 
    std::uniform_real_distribution<float> distr_x_position;
    std::uniform_real_distribution<float> distr_rotation;
    std::uniform_real_distribution<float> distr_max_rotation_speed;
    std::uniform_real_distribution<float> distr_max_object_scalar;
    std::uniform_int_distribution<int> distr_junk_index;
    
    Vector2 junk_speed{0.0f, 0.0f};
    Vector2 junk_breaking_dir_speed{0.0f, 0.0f};

public:
    JunkManager(
        std::vector<Junk> active_junk = std::vector<Junk>(), 
        std::vector<Junk> available_junk = std::vector<Junk>(),
        int max_junk = 0,
        Rectangle game_bounds = Rectangle{0,0,1.0f,1.0f},
        float max_rotation_speed = 0.0f,
        float max_object_scalar = 1.0f
    );
    void add_junk(Junk junk);
    void spawn_junk();
    size_t get_max_junk() const;
    void set_junk_speed(Vector2 speed);
    void set_junk_breaking_dir_speed(Vector2 speed);

    void draw_active_junk();
    void check_collisions(const Ship& ship, bool debug = false);
};