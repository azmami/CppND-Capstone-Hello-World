#ifndef GAME_H
#define GAME_H

#include "renderer.h"
#include "controller.h"

class Game
{
public:
   Game();
   void Run(Controller &controller, 
            Renderer &renderer,
            std::size_t target_frame_duration);

private:

};

#endif