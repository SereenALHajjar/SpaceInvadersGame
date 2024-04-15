#include "laser.hpp"
#include <iostream>
Laser::Laser(Vector2 position, int speed)
{
    this -> position = position ; 
    this -> speed = speed ;
    active = true ; 
}

Laser::~Laser()
{
}

void Laser::Draw()
{
    if(active)
    DrawRectangle(position.x , position.y , 4 , 15 , Color{243 , 216 , 63 , 255}) ;
}

void Laser::Update()
{
    if(active)
    {
    position.y+=speed ;
        if(position.y > GetScreenHeight()-70 || position.y <=25)
        {
            active = false ; 
        }
    }
}

Rectangle Laser::GetRec()
{
    return {position.x, position.y , 4 , 15} ;
}
