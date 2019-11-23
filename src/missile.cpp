#include "missile.h"

/**
 * Constructor for Missile
 * This takes the position x and y as parameters to set pos_ member variable.
 * This initializes the radius too.
 */ 
Missile::Missile(int pos_x, int pos_y)
{ 
   pos_ = Position(pos_x, pos_y);
   SetRadius(5);
}

/**
 * Update the position of y.
 */ 
void Missile::Update()
{
   pos_.y -= 5;
}

