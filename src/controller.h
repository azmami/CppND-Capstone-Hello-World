#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "spaceship.h"

class Controller
{
public:
   void HandleInput(bool &running, Spaceship &spaceship) const;

private:
   void ChangeAngle(Spaceship &spaceship, Spaceship::KeyEvent input) const;
   void Move(Spaceship &spaceship, Spaceship::KeyEvent input) const;
   void Fire(Spaceship &spaceship, int pos_x, int pox_y) const;
};

#endif