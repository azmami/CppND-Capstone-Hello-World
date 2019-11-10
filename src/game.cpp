#include "game.h"
#include "renderer.h"

Game::Game(std::size_t screen_width,
          std::size_t screen_height) :
          spaceship_(screen_width, screen_height)
{

}

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

   // initialize the position of spaceship to the center of screen
   spaceship_.pos_x_ = renderer.GetScreenWidth() / 2;
   spaceship_.pos_y_ = renderer.GetScreenHeight() / 2;

   // show title
   renderer.UpdateWindowTitle();

   while (running)
   {
      frame_start = SDL_GetTicks();

      controller.HandleInput(running, spaceship_);
      Update();
      renderer.Render(spaceship_);

      frame_end = SDL_GetTicks();
      frame_count++;
      frame_duration = frame_end - frame_start;

      if (frame_duration < target_frame_duration)
      {
         SDL_Delay(target_frame_duration - frame_duration);
      }
   }  
}

void Game::Update()
{
   if (!spaceship_.IsAlive()) return;

   spaceship_.Update();
}