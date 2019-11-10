#include "controller.h"
#include "spaceship.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "SDL.h"

void Controller::ChangeAngle(Spaceship &spaceship, Spaceship::KeyEvent input) const
{
   if (input == Spaceship::KeyEvent::kLeft)
   {
      spaceship.velocity_x_ = spaceship.velocity_x_ - 2;
   }
   else
   {
      spaceship.velocity_x_ = spaceship.velocity_x_ + 2;
   }
   spaceship.velocity_x_ = std::clamp(spaceship.velocity_x_, Spaceship::MAX_VELOCITY * -1, Spaceship::MAX_VELOCITY);
}

void Controller::Move(Spaceship &spaceship, Spaceship::KeyEvent input) const
{
   if (input == Spaceship::KeyEvent::kUp)
   {
      spaceship.velocity_y_ = spaceship.velocity_y_ - 2;
   }
   else
   {
      spaceship.velocity_y_ = spaceship.velocity_y_ + 2;
   }
   spaceship.velocity_y_ = std::clamp(spaceship.velocity_y_, Spaceship::MAX_VELOCITY * -1, Spaceship::MAX_VELOCITY);
}

void Controller::Fire(Spaceship &spaceship, int pos_x, int pos_y) const
{
   spaceship.Fire(pos_x, pos_y);
}

void Controller::HandleInput(bool &running, Spaceship &spaceship) const
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
               Move(spaceship, Spaceship::KeyEvent::kUp);
               std::cout << "up\n";
            break;
            case SDLK_DOWN:
               Move(spaceship, Spaceship::KeyEvent::kDown);
               std::cout << "down\n";
            break;
            case SDLK_LEFT:
               ChangeAngle(spaceship, Spaceship::KeyEvent::kLeft);
               std::cout << "left\n";
            break;
            case SDLK_RIGHT:
               ChangeAngle(spaceship, Spaceship::KeyEvent::kRight);
               std::cout << "right\n";
            break;
            case SDLK_SPACE:
               std::cout << "space\n";
               Fire(spaceship, spaceship.pos_x_, spaceship.pos_y_);
            break;
         }
      }
   }
}