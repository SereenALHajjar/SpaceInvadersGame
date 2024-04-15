#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>
class Spaceship
{
public:
    Spaceship();
    ~Spaceship();
    void Update();
    void Draw();
    void MoveRight();
    void MoveLeft();
    void FireLaser();
    void Reset();
    std::vector<Laser> laser;
    Rectangle GetRec();

private:
    Sound laser_sound;
    double last_time_fire;
    Texture2D image;
    Vector2 position;
};