#pragma once
#include <raylib.h>

class Alien
{
public:
    Alien(int type, Vector2 position);
    ~Alien();
    void Update(int direction);
    void Draw();
    int GetType();
    static Texture2D alien_images[3];
    // Texture2D image ;
    static void UnloadImages();
    int type;
    Vector2 position;
    Rectangle GetRec();

private:
    /* data */
};
