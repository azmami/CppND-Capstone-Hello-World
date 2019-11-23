#include "enemy.h"
#include <random>
#include <iostream>

/**
 * Constructor for Enemy.
 * This initializes the radius, position, velocity, angle, score and explosion object.
 */ 
Enemy::Enemy()
{
   // initialize the radius
   SetRadius(35);
   
   // initialize the position randomly
   double x = (double) GetRandomNumericValue(0, SCREEN_WIDTH);
   double y = (double) GetRandomNumericValue(0, SCREEN_HEIGHT / 2) * (-1);
   SetCenterPosition(x, y);

   // initialize the velocity
   velo_ = Velocity(1, 1);

   // initialize explosion object
   explosion_ = Explosion();

   // initialize angle randomly
   angle_ = GetRandomNumericValue(0, 5);

   // initialize enemy score 
   score_ = 50;
}

/**
 * This updates the enemy's velocity, position and rotating angle.
 */ 
void Enemy::Update()
{
   velo_ = Velocity(velo_.x, GetRandomNumericValue(0, 10));
   pos_ = Position(pos_.x, pos_.y + velo_.y);
   angle_ = angle_ + GetRandomNumericValue(0, 10) % 360;
}

/**
 * This update the position of the explosion object and then calls Explode function from parent class.
 */ 
void Enemy::Explode()
{
   explosion_.pos_ = this->pos_;
   GameObject::Explode();
}

/**
 * If the explosion is on-going, this returns true.
 */ 
bool Enemy::IsExploding()
{
   return explosion_.IsAlive();
}

/**
 * This returns the pointer of explosion object.
 */ 
Explosion *Enemy::GetExplosion()
{
   return &explosion_;
}

/**
 * This returns the score of the enemy.
 */  
int Enemy::GetScore() const
{
   return score_;
}