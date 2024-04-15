#include <raylib.h>
#include "game.hpp"
#include "alien.hpp"
#include <string>
std::string FormatWithLeadingZeros(int number, int width)
{
    std::string score = std::to_string(number);
    int leading_zeros = width - score.length();
    score = std::string(leading_zeros, '0') + score;
    return score;
}
int main()
{

    const int screenWidth = 550;
    const int screenHeight = 500;
    const int offset = 50;
    InitWindow(screenWidth + offset, screenHeight + offset * 2, "Space Invaders");
    InitAudioDevice();

    Font font = LoadFontEx("fonts/monogram.ttf", 64, 0, 0);
    Texture2D image = LoadTexture("graphics/spaceship.png");
    SetTargetFPS(60);
    Game sp;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(sp.music);
        // event handling
        sp.HandleInput();
        // updating
        sp.Update();
        // drawing
        BeginDrawing();
        ClearBackground({29, 29, 27, 255});
        DrawRectangleRoundedLines({10, 10, 580, 580}, 0.18f, 20, 1, {243, 216, 63, 255});
        DrawLineEx({25, 530}, {575, 530}, 1, {243, 216, 63, 255});
        std::string msg = "";
        if (sp.run)
            msg = "LEVEL 01";
        else
            msg = "GAME OVER";
        DrawTextEx(font, msg.c_str(), {430, 540}, 24, 2, {243, 216, 63, 255});
        float x = 50;
        for (int i = 0; i < sp.lives; i++)
        {
            DrawTextureV(image, {x, 545}, WHITE);
            x += 50;
        }
        DrawTextEx(font, "SCORE", {25, 15}, 24, 2, {243, 216, 63, 255});
        DrawTextEx(font, FormatWithLeadingZeros(sp.score, 5).c_str(), {25, 40}, 24, 2, {243, 216, 63, 255});
        DrawTextEx(font, "HIGH-SCORE", {430, 15}, 24, 2, {243, 216, 63, 255});
        DrawTextEx(font, FormatWithLeadingZeros(sp.high_score, 5).c_str(), {485, 40}, 24, 2, {243, 216, 63, 255});
        sp.Draw();
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}