#include "gameobject.h"
#include <algorithm>
#include <random>

bool GameObject::IsAlive() const
{
   return is_alive_;
}

void GameObject::SetRadius(int radius)
{
   radius_ = radius;
}

int GameObject::GetRadius()
{
   return radius_;
}

void GameObject::SetIsAlive(bool is_alive)
{
   is_alive_ = is_alive;
}

bool GameObject::CollisionDetected(const GameObject &opponent)
{
   return std::pow(pos_.x - opponent.pos_.x, 2) + std::pow(pos_.y - opponent.pos_.y, 2) <= std::pow(radius_ + opponent.radius_, 2);
}

void GameObject::Explode()
{
   is_alive_ = false;
}

void GameObject::SetCenterPosition(double left_x, double top_y)
{
   pos_ = {left_x + radius_, top_y + radius_};
}

Position GameObject::GetTopLeftCornerPosition() const
{
   return {pos_.x - radius_, pos_.y - radius_};
}

int GameObject::GetRandomNumericValue(int from, int to) const
{
   std::random_device rd;
   std::mt19937 mt(rd());
   return mt() % (to - from) - from;
}