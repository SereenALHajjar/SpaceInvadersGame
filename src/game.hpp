#pragma once
#include "spaceship.hpp"
#include <raylib.h>
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
#include <fstream>

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    bool run ;      
    int lives ;
    int score ;
    int high_score ; 
    Music music ; 
private:
    Spaceship spaceship;
    void DeleteInactiveLaser();
    std::vector<Alien> aliens;
    std::vector<Obstacle> obstacles;
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootLaser();
    void GameOver() ;
    void Reset() ;
    void CheckForHighScore() ;
    void InitGame() ;
    void SaveHighScoreToFile(int high_score) ;
    int LoadHighScoreFromFile() ;
    int aliens_direction;
    std::vector<Laser> aliens_laser;
    constexpr static float alien_laser_shoot_interval = 0.35;
    float time_last_alien_fired;
    MysteryShip mystery_ship ;
    float mystery_ship_spawn_interval ;
    float time_last_spawn ; 
    void CheckForCollision() ; 
    Sound explosion_sound ;
};
