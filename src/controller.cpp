#include "controller.h"
#include "spaceship.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "SDL.h"

/**
 * MoveX is called when either left or right key is pressed.
 * If it's left key, it decrements the X velocity by 2.
 * If it's right key, it increments the X velocity by 2.
 * After decrementing or incrementing the X velocity, it gets clamp value so that it does not exceed speed limit.
 */ 
void Controller::MoveX(Spaceship &spaceship, Spaceship::KeyEvent input) const
{
   if (input == Spaceship::KeyEvent::kLeft)
   {
      spaceship.velo_.x -= 2;
   }
   else
   {
      spaceship.velo_.x += 2;
   }
   // If x velocity exceeds the max velocity, replace velo_.x with MAX_VELOCITY value
   spaceship.velo_.x = std::clamp((int) spaceship.velo_.x, Spaceship::MAX_VELOCITY * -1, Spaceship::MAX_VELOCITY);
}

/**
 * MoveY is called when either up or down key is pressed.
 * If it's up key, it decrements the Y velocity by 2.
 * If it's down key, it increments the Y velocity by 2.
 * After decrementing or incrementing the Y velocity, it gets clamp value so that it does not exceed speed limit.
 */ 
void Controller::MoveY(Spaceship &spaceship, Spaceship::KeyEvent input) const
{
   if (input == Spaceship::KeyEvent::kUp)
   {
      spaceship.velo_.y -= 2;
   }
   else
   {
      spaceship.velo_.y += 2;
   }
   // If y velocity exceeds the max velocity, replace velo_.y with MAX_VELOCITY value
   spaceship.velo_.y = std::clamp((int) spaceship.velo_.y, Spaceship::MAX_VELOCITY * -1, Spaceship::MAX_VELOCITY);
}

/**
 * Fire is called when space key is pressed.
 * It fires the missile by using Fire function of Spaceship class.
 */ 
void Controller::Fire(Spaceship &spaceship) const
{
   spaceship.Fire();
}

/**
 * This function handles inputs from Keyboard and quit event.
 * If quit event happens, running boolean flag gets updated to false.
 * This function accepts up, down, left, right, space and C keyboard events. 
 */ 
void Controller::HandleInput(bool &running, bool &continue_triggered, Spaceship &spaceship) const
{
   SDL_Event e;
   while (SDL_PollEvent(&e))
   {
      if (e.type == SDL_QUIT)
      {
         running = false;
      } 
      else if (e.type == SDL_KEYDOWN)
      {
         switch(e.key.keysym.sym)
         {
            case SDLK_UP:
               MoveY(spaceship, Spaceship::KeyEvent::kUp);
               break;
            case SDLK_DOWN:
               MoveY(spaceship, Spaceship::KeyEvent::kDown);
               break;
            case SDLK_LEFT:
               MoveX(spaceship, Spaceship::KeyEvent::kLeft);
               break;
            case SDLK_RIGHT:
               MoveX(spaceship, Spaceship::KeyEvent::kRight);
               break;
            case SDLK_SPACE:
               if (spaceship.IsAlive())
                 Fire(spaceship);
               break;
            case SDLK_c:
               if (!spaceship.IsAlive())
                  continue_triggered = true;
               break;
         }
      }
   }
}