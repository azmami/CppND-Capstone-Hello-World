#ifndef EXPLOSION_
#define EXPLOSION_

#include "gameobject.h"
class Explosion : public GameObject
{
public:
   int alpha_; // this is used for making the image of explosion gradually disappeared on the screen.
   Explosion();
   void Update();
};

#endif