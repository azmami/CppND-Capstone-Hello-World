#include "spaceship.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <deque>

/**
 * Constructor for Spaceship.
 * It initializes the radius, the first position, velocity.
 */ 
Spaceship::Spaceship()
{
   SetRadius(25);
   SetCenterPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
   velo_ = Velocity(0, 1);
}

/**
 * This updates the position of spaceship as well as positions of fired missiles.
 */ 
void Spaceship::Update()
{
   // Update the position
   pos_.x += velo_.x;
   pos_.y += velo_.y;

   // Adjusting the position after adding velocity to avoid spaceship being out of view
   pos_.x = std::clamp((int) pos_.x, GetRadius(), SCREEN_WIDTH - GetRadius());
   if (pos_.x <= GetRadius() || pos_.x >= SCREEN_WIDTH - GetRadius())
   {
      velo_.x = 0;
   }
   
   pos_.y = std::clamp((int) pos_.y, GetRadius(), SCREEN_HEIGHT - GetRadius());
   if (pos_.y <= GetRadius() || pos_.y >= SCREEN_HEIGHT - GetRadius())
   {
      velo_.y = 0;
   }

   // update missiles' position
   std::for_each(missiles_.begin(), missiles_.end(), [](Missile &m)
   {
      m.Update();
   });

   // if the missiles are out of the screen (i.e. y < 0), remove them from deque 
   auto missiles_to_remove = std::remove_if(missiles_.begin(), missiles_.end(), [](Missile &m) {
      return m.pos_.y < 0 || !m.IsAlive();
   });

   missiles_.erase(missiles_to_remove, missiles_.end());
}

/**
 * If a user presses space key, this function is called.
 * It's limited that the total missile count shown on the window at the same time is only 5.
 */ 
void Spaceship::Fire()
{
   if (missiles_.size() < 5) 
   {
      missiles_.push_back(Missile(pos_.x, pos_.y - 10));
   }
}

