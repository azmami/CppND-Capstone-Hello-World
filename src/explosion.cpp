#include "explosion.h"
#include <iostream>

/**
 * Constructor of Explosion.
 */  
Explosion::Explosion()
{
   alpha_ = 255;
   SetRadius(40);
   SetIsAlive(true);
}

void Explosion::Update()
{
   alpha_ -= 10; 
   if (alpha_ < 0) Explode();
}