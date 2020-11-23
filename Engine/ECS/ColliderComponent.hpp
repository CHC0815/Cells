#pragma once

#include <string>
#include <SDL.h>
#include "ECS.hpp"
#include "Components.hpp"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;

    TransformComponent* transform;

    ColliderComponent(std::string tag)
    {
        this->tag = tag;
    }

    void init() override
    {
        if(!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        Game::colliders.push_back(this);
    }

    void update() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = static_cast<int>(transform->width * transform->scale.x);
        collider.h = static_cast<int>(transform->height * transform->scale.y);
    }

};