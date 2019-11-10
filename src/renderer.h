#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "spaceship.h"

class Renderer
{
public:
   Renderer(const std::size_t screen_width,
            const std::size_t screen_height);
   ~Renderer();

   void Render(Spaceship const spaceship);
   void UpdateWindowTitle();

   std::size_t GetScreenWidth();
   std::size_t GetScreenHeight();
private:
   SDL_Window *sdl_window_;
   SDL_Renderer *sdl_renderer_;
   SDL_Texture *sdl_texture_;
   SDL_Surface *sdl_surface_;

   const std::size_t screen_width_;
   const std::size_t screen_height_;
};

#endif