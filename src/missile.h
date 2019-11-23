#ifndef MISSILE_
#define MISSILE_
#include "gameobject.h"

/**
 * Missile class.
 */ 
class Missile : public GameObject
{
public:
   Missile(int pos_x, int pos_y);
   void Update();
};

#endif