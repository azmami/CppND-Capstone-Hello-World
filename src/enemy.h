#ifndef ENEMY_H
#define ENEMY_H
#include "gameobject.h"
#include "explosion.h"

class Enemy : public GameObject
{
public:
   Enemy();
   void Update();
   void Explode();
   bool IsExploding();
   Explosion *GetExplosion();
   int GetScore() const;

private:
   Explosion explosion_;
   int score_;
};

#endif