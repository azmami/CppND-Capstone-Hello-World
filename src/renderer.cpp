#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height) :
                   screen_width_(screen_width),
                   screen_height_(screen_height)
{
   if (SDL_Init(SDL_INIT_VIDEO) < 0)
   {
      std::cerr << "SDL could not initialize.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
   }

   sdl_window_ = SDL_CreateWindow("Asteroids",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  screen_width,
                                  screen_height,
                                  SDL_WINDOW_SHOWN);
   if (nullptr == sdl_window_)
   {
      std::cerr << "Window could not be created.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
   }

   sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
   if (nullptr == sdl_renderer_)
   {
      std::cerr << "Renderer could not be created.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
   }
}

Renderer::~Renderer()
{
   SDL_DestroyWindow(sdl_window_);
   SDL_Quit();
}

void Renderer::Render()
{
   SDL_SetRenderDrawColor(sdl_renderer_, 0x1E, 0x1E, 0x1E, 0xFF);
   SDL_RenderClear(sdl_renderer_);
   SDL_SetRenderDrawColor(sdl_renderer_, 0x00, 0x7A, 0xCC, 0xFF);
   SDL_RenderPresent(sdl_renderer_);
}

void Renderer::UpdateWindowTitle()
{
   std::string title {"HogeHoge"};
   SDL_SetWindowTitle(sdl_window_, title.c_str());
}