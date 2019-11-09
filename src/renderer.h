#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"

class Renderer
{
public:
   Renderer(const std::size_t screen_width,
            const std::size_t screen_height);
   ~Renderer();

   void Render();
   void UpdateWindowTitle();
private:
   SDL_Window *sdl_window_;
   SDL_Renderer *sdl_renderer_;

   const std::size_t screen_width_;
   const std::size_t screen_height_;
};

#endif