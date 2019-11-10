#include "spaceship.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <deque>

Spaceship::Spaceship(std::size_t screen_width,
                     std::size_t screen_height)
{
   x_boundary_min_ = 0;
   x_boundary_max_ = screen_width - 50;
   y_boundary_min_ = 0;
   y_boundary_max_ = screen_height - 50;

}

void Spaceship::Update()
{
   pos_x_ += velocity_x_;
   pos_x_ = std::clamp(pos_x_, x_boundary_min_, x_boundary_max_);
   if (pos_x_ == x_boundary_min_ || pos_x_ == x_boundary_max_)
   {
      velocity_x_ = 0;
   }

   pos_y_ += velocity_y_;
   pos_y_ = std::clamp(pos_y_, y_boundary_min_, y_boundary_max_);   
   if (pos_y_ == y_boundary_min_ || pos_y_ == y_boundary_max_)
   {
      velocity_y_ = 0;
   }
   
   // update missiles' position
   std::for_each(missiles_.begin(), missiles_.end(), [this](SDL_Point &p)
   {
      p.y = p.y - 5;
   });

   // if the missiles are off the screen (i.e. y < 0), remove it from deque 
   auto keep = std::remove_if(missiles_.begin(), missiles_.end(), [](SDL_Point &p) {
      return p.y < 0;
   });
   missiles_.erase(keep, missiles_.end());
}

void Spaceship::Fire(int pos_x, int pos_y)
{
   missiles_.push_back(SDL_Point {pos_x, pos_y});
}

bool Spaceship::IsAlive()
{
   return alive_;
}
