#pragma once
#include <raylib.h>

class MysteryShip
{
public:
    MysteryShip(/* args */);
    ~MysteryShip();
    void Update();
    void Draw();
    void Spawn();
    Rectangle GetRec();
    bool alive;

private:
    Vector2 position;
    Texture2D image;
    int speed;
};
