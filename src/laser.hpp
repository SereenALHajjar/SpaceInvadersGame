#pragma once
#include <raylib.h>
class Laser
{
public:
    Laser(Vector2 position, int speed);
    ~Laser();
    void Draw();
    void Update();
    bool active;
    Rectangle GetRec();

private:
    Vector2 position;
    int speed;
};