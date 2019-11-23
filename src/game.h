#ifndef GAME_H
#define GAME_H

#include "renderer.h"
#include "controller.h"
#include "gameobject.h"
#include "enemy.h"
#include <deque>

class Game
{
public:
   Game();
   void Initialize();
   void Run(Controller &controller, 
         Renderer &renderer,
         std::size_t target_frame_duration);
   void Update();
   void CollisionDetected(Spaceship &s);
   void AddScore(int score);
   int GetScore();

private:
   Spaceship spaceship_;
   std::deque<Enemy> enemies_;
   int score_;
};

#endif