#include "game.hpp"
#include <iostream>
Game::Game()
{
    music = LoadMusicStream("sounds/music.ogg") ;
    PlayMusicStream(music) ;
    explosion_sound = LoadSound("sounds/explosion.ogg");

    InitGame() ;
}
Game::~Game()
{
    Alien::UnloadImages();
    UnloadMusicStream(music) ;
    UnloadSound(explosion_sound) ;
}

void Game::Draw()
{
    // if(!run) return ; 
    spaceship.Draw();
    for (Laser &laser : spaceship.laser)
    {
        laser.Draw();
    }
    for (Obstacle &obs : obstacles)
    {
        obs.Draw();
    }
    for (Alien &al : aliens)
    {
        al.Draw();
    }
    for (Laser &laser : aliens_laser)
    {
        laser.Draw();
    }
    mystery_ship.Draw();
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear() ;
    aliens_laser.clear() ;
    obstacles.clear() ;
}
void Game::InitGame()
{
    score =0 ; 
    high_score = LoadHighScoreFromFile() ;
obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliens_direction = 1;
    time_last_alien_fired = 0.0;
    time_last_spawn = 0.0;
    mystery_ship_spawn_interval = GetRandomValue(10, 20);
    lives = 3 ; 
    run = true ;
}
void Game::CheckForHighScore()
{
    high_score = (high_score > score) ? high_score : score ;
    SaveHighScoreToFile(high_score) ;
}
void Game::SaveHighScoreToFile(int high_score)
{
    std::ofstream high_score_file("highScore.txt") ;
    if(high_score_file.is_open())
    {
        high_score_file<<high_score ;
        high_score_file.close() ;
    }
    else std::cerr<<"Failed to save high score " <<std::endl ;


}

int Game::LoadHighScoreFromFile()
{
    int high_score=0 ; 
    std::ifstream high_score_file("highScore.txt") ;
    if(high_score_file.is_open())
    {
        high_score_file>>high_score ;
        high_score_file.close() ;
    }
    else std::cerr<<"Failed to load form file"<<std::endl ;
    return high_score ;
}

void Game::Update()
{
    if(!run) 
    {
        if(IsKeyDown(KEY_ENTER))
        {
            Reset() ;
            InitGame() ;
        }
        return ;
    } 
    double current_time = GetTime();
    if (current_time - time_last_spawn >= mystery_ship_spawn_interval)
    {
        mystery_ship.Spawn();
        time_last_spawn = GetTime();
        mystery_ship_spawn_interval = GetRandomValue(10, 20);
    }
    for (Laser &laser : spaceship.laser)
    {
        laser.Update();
    }
    DeleteInactiveLaser();
    AlienShootLaser();
    for (Laser &laser : aliens_laser)
    {
        laser.Update();
    }
    MoveAliens();
    mystery_ship.Update();
    CheckForCollision();
}

void Game::HandleInput()
{
    if(!run) return ;
    if (IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
    }
    if (IsKeyDown(KEY_SPACE))
    {
        spaceship.FireLaser();
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacle_width = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacle_width)) / 5;
    for (int i = 0; i < 4; i++)
    {
        float offset_x = (i + 1) * gap + i * obstacle_width;
        obstacles.push_back(Obstacle({offset_x, float(GetScreenHeight() - 150)}));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens1;
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 11; column++)
        {
            int alien_type;
            if (row == 0)
                alien_type = 3;
            else if (row == 1 || row == 2)
                alien_type = 2;
            else
                alien_type = 1;
            float x = 75 + column * 40;
            float y = 60 + row * 40;
            aliens1.push_back(Alien(alien_type, {x, y}));
        }
    }
    return aliens1;
}

void Game::MoveAliens()
{
    for (Alien &al : aliens)
    {
        if (al.position.x + al.alien_images[al.type - 1].width > GetScreenWidth()-25)
        {
            aliens_direction = -1;
            MoveDownAliens(2);
        }
        if (al.position.x < 25)
        {
            aliens_direction = 1;
            MoveDownAliens(2);
        }
        al.Update(aliens_direction);
    }
}

void Game::MoveDownAliens(int distance)
{
    for (Alien &al : aliens)
    {
        al.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double current_time = GetTime();
    if (current_time - time_last_alien_fired >= alien_laser_shoot_interval && aliens.size() != 0)
    {

        int random_index = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[random_index];
        aliens_laser.push_back(Laser({alien.position.x + alien.alien_images[alien.type - 1].width / 2,
                                      alien.position.y + alien.alien_images[alien.type - 1].height},
                                     6));
        time_last_alien_fired = GetTime();
    }
}

void Game::GameOver()
{
    run = false ; 
}

void Game::CheckForCollision()
{
    for (Laser &laser : spaceship.laser)
    {
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if (CheckCollisionRecs(laser.GetRec(), it->GetRec()))
            {
                PlaySound(explosion_sound) ;
                if(it->type == 1) score+=100 ;
                else if(it->type ==2) score+=200 ;
                else score+=300 ;
                it = aliens.erase(it);
                laser.active = false;
                CheckForHighScore() ;
            }
            else
                it++;
            
        }
        for (Obstacle &obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetRec(), laser.GetRec()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                    it++;
            }
        }
        if (CheckCollisionRecs(mystery_ship.GetRec(), laser.GetRec()))
        {
            score+=500 ;
            PlaySound(explosion_sound) ;
            mystery_ship.alive = false;
            laser.active = false;
        }
    }
    for (Laser &laser : aliens_laser)
    {
        if (CheckCollisionRecs(laser.GetRec(), spaceship.GetRec()))
        {
            laser.active = false;
            lives-- ;
            if(lives == 0)
            {
                GameOver() ;
            }
        }
        for (Obstacle &obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetRec(), laser.GetRec()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                    it++;
            }
        }
    }
    for(Alien & alien : aliens)
    {
        for(Obstacle & obstacle : obstacles)
        {
            auto it  = obstacle.blocks.begin() ;
            while(it != obstacle.blocks.end())
            {
            if(CheckCollisionRecs(it -> GetRec() , alien.GetRec()))
            {
                it = obstacle.blocks.erase(it) ;
            }
            else it++ ;

            }
        }
        if(CheckCollisionRecs(alien.GetRec() , spaceship.GetRec()))
        {
            // std::cout<<"hittttt\n" ;
            GameOver() ;
        }
    }
}

void Game::DeleteInactiveLaser()
{
    for (auto it = spaceship.laser.begin(); it != spaceship.laser.end();)
    {
        if (it->active == false)
            spaceship.laser.erase(it);
        else
            it++;
    }
    for (auto it = aliens_laser.begin(); it != aliens_laser.end();)
    {
        if (it->active == false)
            aliens_laser.erase(it);
        else
            it++;
    }
}
