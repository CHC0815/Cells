#include "Collision.hpp"
#include "ECS\ColliderComponent.hpp"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
    if(
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y
    )
    {
        return true;
    }
    return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
    return AABB(colA.collider, colB.collider);
}