#include <iostream>
#include "controller.h"
#include "renderer.h"
#include "game.h"

/**
 * Main function.
 */ 
int main() {
   constexpr std::size_t frame_per_second = 60;
   constexpr std::size_t ms_per_frame = 1000 / frame_per_second;
   
   Game game;
   Controller controller;
   Renderer renderer; 
   game.Run(controller, renderer, ms_per_frame);
   return 0;
}