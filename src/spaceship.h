#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "SDL.h"

class Spaceship
{
public:
   enum class Direction { kUp, kDown, kLeft, kRight };
   Spaceship() {};
   void Update();

   Direction direction_ = Direction::kUp;

   float speed_ = 0.1f;
   bool alive_ = true;
   float pos_x_;
   float pos_y_;

private:
   
}

#endif