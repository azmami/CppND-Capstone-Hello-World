#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "SDL.h"
#include <deque>

static const double PI = 3.141592653589793;

class Spaceship
{
public:
   enum class KeyEvent { kUp, kDown, kLeft, kRight }; 

   static constexpr int MAX_VELOCITY = 6;

   Spaceship(std::size_t screen_width, std::size_t screen_height);
   void Update();
   bool IsAlive();
   
   void Fire(int pos_x, int pos_y);

   int velocity_x_ = 0;
   int velocity_y_ = -1;

   int pos_x_;
   int pos_y_;

   std::deque<SDL_Point> missiles_ {};
  // const std::string image_path_ = "../asset/spaceship.png";
private:
   bool alive_ = true;
   int x_boundary_min_;
   int x_boundary_max_;
   int y_boundary_min_;
   int y_boundary_max_;
   
};

#endif