#include <iostream>
#include "controller.h"
#include "renderer.h"
#include "game.h"

int main() {
   constexpr std::size_t screen_width = 640;
   constexpr std::size_t screen_height = 1136;
   constexpr std::size_t frame_per_second = 60;
   constexpr std::size_t ms_per_frame = 1000 / frame_per_second;
   
   Controller controller;
   Renderer renderer(screen_width, screen_height);
   Game game(screen_width, screen_height);
   game.Run(controller, renderer, ms_per_frame);
   return 0;
}