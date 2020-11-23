#pragma once
#include "Components.hpp"
#include "SDL.h"
#include "../TextureManager.hpp"

class SpriteComponent : public Component
{
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

public:

    SpriteComponent() = default;
    SpriteComponent(const char* path)
    {
        setTexture(path);
        srcRect.w = 32;
        srcRect.h = 32;
    }

    SpriteComponent(const char* path, int w, int h)
    {
        srcRect.w = w;
        srcRect.h = h;
        setTexture(path);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTexture(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        if(!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
    }

    void update() override
    {
        destRect.w = static_cast<int>(transform->width * transform->scale.x);
        destRect.h = static_cast<int>(transform->height * transform->scale.y);
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }

};