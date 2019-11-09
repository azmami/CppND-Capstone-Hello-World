#include "game.h"
#include "renderer.h"

Game::Game()
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
   while (running)
   {
      frame_start = SDL_GetTicks();

      controller.HandleInput(running);

      renderer.Render();
      renderer.UpdateWindowTitle();

      frame_end = SDL_GetTicks();

      frame_count++;
      frame_duration = frame_end - frame_start;

      if (frame_duration < target_frame_duration)
      {
         SDL_Delay(target_frame_duration - frame_duration);
      }
   }  
}