#include "alien.hpp"

Texture2D Alien::alien_images[3]= { } ;

Alien::Alien(int type, Vector2 position)
{
    this ->type = type ; 
    this ->position = position ;
    if(alien_images[type -1].id == 0)
    {
    if(type == 1)
        alien_images[0] = LoadTexture("graphics/alien_1.png") ;
    else if(type == 2)
        alien_images[1] = LoadTexture("graphics/alien_2.png") ;
    else alien_images[2] = LoadTexture("graphics/alien_3.png") ;
    }
}

Alien::~Alien()
{
//    UnloadImages() ;
}

void Alien::Update(int direction)
{
    position.x+=direction ;
}

void Alien::Draw()
{
    DrawTextureV(alien_images[type-1],position , WHITE) ;
}

int Alien::GetType()
{
    return type ; 
}

void Alien::UnloadImages()
{
    for(int i=0 ; i<3 ; i++)
    UnloadTexture(alien_images[i]) ;
}

Rectangle Alien::GetRec()
{
    return {position.x , position.y , float(alien_images[type-1].width) , float(alien_images[type-1].height)} ;
}
