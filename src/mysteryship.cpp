#include "mysteryship.hpp"

MysteryShip::MysteryShip()
{
    image = LoadTexture("graphics/mystery.png");
    alive = false;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

void MysteryShip::Update()
{
    if (alive)
    {
        position.x += speed;
        if (position.x < 25 || position.x > GetScreenWidth() - image.width - 25)
            alive = false;
    }
}

void MysteryShip::Draw()
{
    if (alive)
    {
        DrawTextureV(image, position, WHITE);
    }
}

void MysteryShip::Spawn()
{
    position.y = 90;
    int side = GetRandomValue(0, 1);
    if (!side)
    {
        speed = 3;
        position.x = 25;
    }
    else
    {
        speed = -3;
        position.x = GetScreenWidth() - image.width - 25;
    }
    alive = true;
}

Rectangle MysteryShip::GetRec()
{
    if (alive)
        return {position.x, position.y, image.width, image.height};
    return {position.x, position.y, 0, 0};
}
