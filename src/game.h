#ifndef GAME_H
#define GAME_H

#include "renderer.h"
#include "controller.h"
#include "spaceship.h"
#include "asteroid.h"
#include <deque>


class Game
{
public:
   Game(std::size_t screen_width, std::size_t screen_height);
   void Run(Controller &controller, 
         Renderer &renderer,
         std::size_t target_frame_duration);
   void Update();

private:
   Spaceship spaceship_;
   std::deque<Asteroid> asteroids_;
   std::size_t screen_width_;
   std::size_t screen_height_;
};

#endif