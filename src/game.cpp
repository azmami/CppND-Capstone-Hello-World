#include "game.h"
#include "renderer.h"
#include <deque>
#include <algorithm>
#include <iostream>

/**
 * Constructor for Game
 */ 
Game::Game()
{
   Initialize();
}

/**
 * This initializes spaceship, total score and enemy objects.
 * This function is to be called when a user presses C key after loosing the game.
 */ 
void Game::Initialize()
{
   // initialize spaceship
   spaceship_ = Spaceship();

   // initialize score
   score_ = 0;

   // clearing up the enemy queue and initialize them again
   enemies_.clear();
   for (std::size_t i = 0; i < 5; ++i)
   {
      enemies_.push_back(Enemy());
   }
}

/**
 * Once game starts, this function keeps handling inputs, updating game objects and rendering by using infinite loop.
 */ 
void Game::Run(Controller &controller,
               Renderer &renderer,
               std::size_t target_frame_duration)
{
   Uint32 title_timestamp = SDL_GetTicks();
   Uint32 frame_start;
   Uint32 frame_end;
   Uint32 frame_duration;
   int frame_count = 0;
   bool running = true;
   bool continue_triggered = false;

   // Show title
   renderer.UpdateWindowTitle();

   while (running)
   {
      frame_start = SDL_GetTicks();

      controller.HandleInput(running, continue_triggered, spaceship_);
      
      // If continue key is pressed, this initializes the game objects and let a user start the game from beginning.
      if (continue_triggered)
      {
         Initialize();
         continue_triggered = false;
      }

      // Update game objects
      Update();

      // Render game objects
      renderer.Render(spaceship_, enemies_, GetScore());

      frame_end = SDL_GetTicks();
      frame_count++;
      frame_duration = frame_end - frame_start;

      if (frame_duration < target_frame_duration)
      {
         SDL_Delay(target_frame_duration - frame_duration);
      }
   }  
}

/**
 * Add the provided score to the total score
 */ 
void Game::AddScore(int score)
{
   score_ = score_ + score;
}

/**
 * Returns the current total score
 */ 
int Game::GetScore()
{
   return score_;
}

/**
 * Updates the game objects: spaceship, missiles, enemies.
 * If spaceship is no longer alive, this function won't update these game objects.
 */ 
void Game::Update()
{
   if (!spaceship_.IsAlive()) 
   {
      return;
   }

   // Update spaceship
   spaceship_.Update();

   // Update missiles
   std::for_each(spaceship_.missiles_.begin(), spaceship_.missiles_.end(), [this](Missile &missile)
   { 
      for(auto enemy = enemies_.begin(); enemy != enemies_.end(); ++enemy)
      {
         if ((*enemy).CollisionDetected(missile))
         {
            AddScore(enemy->GetScore());
            missile.Explode();
            (*enemy).Explode();
         }
      }
   });
   
   // Update enemies
   std::for_each(enemies_.begin(), enemies_.end(), [this](Enemy &enemy) {
      if (enemy.IsAlive())
      {
         enemy.Update();
      }
      else
      {
         enemy.GetExplosion()->Update();
      }
      
      if (enemy.CollisionDetected(spaceship_))
      {
         CollisionDetected(spaceship_);
      }
   });

   // Delete enemies that are out of view
   auto enemies_to_delete = std::remove_if(enemies_.begin(), enemies_.end(), [](Enemy &e) {
      return e.pos_.y > SCREEN_HEIGHT || (!e.IsAlive() && !e.IsExploding());
   });
   enemies_.erase(enemies_to_delete, enemies_.end());

   // If the number of enemies become less than 3, create a new one
   if (enemies_.size() < 3) {
      enemies_.push_back(Enemy());
   }

}

/**
 * If spaceship is collided with enemies, this triggers Explode function of the provided Spaceship object.
 */ 
void Game::CollisionDetected(Spaceship &s)
{ 
   s.Explode();
}
