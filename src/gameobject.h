#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <cmath>
#include <deque>

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 640;

/**
 * This represents a position that has x and y coordinate
 */ 
struct Position
{
   double x;
   double y;
   Position(double pos_x, double pos_y) : x(pos_x), y(pos_y) {};
};

/**
 * This represents a velocity that has x and y direction
 */ 
struct Velocity
{
   double x;
   double y;
   Velocity(double velo_x, double velo_y) : x(velo_x), y(velo_y) {};
};

/**
 * GameObject class
 */ 
class GameObject
{
public:
   Position pos_; // center position of the game object
   Velocity velo_; // velocity of the game object
   int angle_; // angle of the game object 

   GameObject() : pos_(Position(0, 0)), velo_(Velocity(0 ,0)), radius_(0), is_alive_(true), angle_(0) {};
   ~GameObject() {};

   virtual void Update() {};
   bool IsAlive() const;
   void SetIsAlive(bool is_alive);
   int GetRadius();
   void SetRadius(int radius);
   bool CollisionDetected(const GameObject &opponent);
   void Explode();
   void SetCenterPosition(double left_x, double top_y);
   Position GetTopLeftCornerPosition() const;
   int GetRandomNumericValue(int from, int to) const;
private:
   int radius_;
   bool is_alive_;
};

#endif