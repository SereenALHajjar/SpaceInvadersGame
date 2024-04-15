#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("graphics/spaceship.png") ;
    laser_sound = LoadSound("sounds/laser.ogg") ;
    position.x = (GetScreenWidth() - image.width)/2  ;
    position.y = GetScreenHeight() - image.height - 70 ;
    last_time_fire = 0 ;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image) ;
    UnloadSound(laser_sound) ;
}

void Spaceship::Update()
{
}

void Spaceship::Draw()
{
    DrawTextureV(image, position , WHITE) ;
}

void Spaceship::MoveRight()
{
    position.x+=5 ;
    if( position.x >  (GetScreenWidth() - image.width - 25))
        position.x =(GetScreenWidth() - image.width-25) ;
}

void Spaceship::MoveLeft()
{
    position.x-=5 ; 
    if(position.x < 25)
        position.x = 25 ;
}

void Spaceship::FireLaser()
{
    if(GetTime() - last_time_fire >=0.35)
    {
    laser.push_back(Laser({position.x+image.width/2 -2 , position.y} , -6)) ;
    last_time_fire = GetTime() ;
    PlaySound(laser_sound) ;
    }

}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth()-image.width )/2.0 ;
    position.y = GetScreenHeight() - image.height-70;
    laser.clear() ;
}

Rectangle Spaceship::GetRec()
{
    return {position.x , position.y , float(image.width) , float(image.height)};
}
