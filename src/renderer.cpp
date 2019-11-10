#include "renderer.h"
#include "spaceship.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <future>
#include "SDL.h"
#include "SDL_image.h"

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

   int img_flag = IMG_INIT_PNG;
   if (IMG_Init(img_flag) && img_flag)
   {
      sdl_surface_ = IMG_Load("../asset/spaceship.png");
      if (!sdl_surface_)
      {
         std::cerr << "IMG_Load failed: " << IMG_GetError() << "\n";
      }
      else
      {
         sdl_texture_ = SDL_CreateTextureFromSurface(sdl_renderer_, sdl_surface_);
      }
   }
   else
   {
      std::cerr << "IMG_Init failed: " << IMG_GetError() << "\n";
   }
}

Renderer::~Renderer()
{
   IMG_Quit();
   SDL_FreeSurface(sdl_surface_);
   SDL_DestroyRenderer(sdl_renderer_);
   SDL_DestroyTexture(sdl_texture_);
   SDL_DestroyWindow(sdl_window_);
   SDL_Quit();
}

void Renderer::Render(Spaceship const spaceship)
{
   int w, h;
   SDL_QueryTexture(sdl_texture_, NULL, NULL, &w, &h);
   SDL_Rect imageRect = (SDL_Rect){0, 0, w, h};
   SDL_Rect drawRect = (SDL_Rect){spaceship.pos_x_, spaceship.pos_y_, w, h};

   // clear screen
   SDL_SetRenderDrawColor(sdl_renderer_, 200, 200, 200, 255);
   SDL_RenderClear(sdl_renderer_);

   // render spaceship
   SDL_RenderCopy(sdl_renderer_, sdl_texture_, &imageRect, &drawRect);

   // render missiles
   std::for_each(spaceship.missiles_.begin(), spaceship.missiles_.end(), [spaceship, this] (SDL_Point p) {
      SDL_Rect missileRect = (SDL_Rect) {p.x, p.y, 10, 10};
      SDL_SetRenderDrawColor(sdl_renderer_, 255, 0, 0, 255);
      SDL_RenderFillRect(sdl_renderer_, &missileRect);
   });

   SDL_RenderPresent(sdl_renderer_);
}

void Renderer::UpdateWindowTitle()
{
   std::string title = "Spaceshooter";
   SDL_SetWindowTitle(sdl_window_, title.c_str());
}

std::size_t Renderer::GetScreenHeight()
{
   return screen_height_;
}


std::size_t Renderer::GetScreenWidth()
{
   return screen_width_;
}