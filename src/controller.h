#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "spaceship.h"

/**
 * Controller class listens to keyboard events (and quit event).
 */ 
class Controller
{
public:
   void HandleInput(bool &running, bool &continue_triggered, Spaceship &spaceship) const;

private:
   void MoveY(Spaceship &spaceship, Spaceship::KeyEvent input) const;
   void MoveX(Spaceship &spaceship, Spaceship::KeyEvent input) const;
   void Fire(Spaceship &spaceship) const;
   void Continue(Spaceship &spaceship) const;
};

#endif