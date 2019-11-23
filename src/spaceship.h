#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "SDL.h"
#include "gameobject.h"
#include "missile.h"
#include "explosion.h"
#include <deque>

static const double PI = 3.141592653589793;

class Spaceship : public GameObject
{
public:
   enum class KeyEvent { kUp, kDown, kLeft, kRight }; 
   static constexpr int MAX_VELOCITY = 6;

   std::deque<Missile> missiles_ {};

   Spaceship();
   void Fire();
   void Update();
};

#endif