#pragma once

#include "ECS.hpp"
#include "Components.hpp"
#include <SDL.h>

class TileComponent : public Component{

public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    SDL_Rect tileRect;
    int tileID;
    char* path;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        switch(tileID)
        {
            case 0:
                path = (char*)"assets/water.png";
                break;
            case 1:
                path = (char*)"assets/dirt.png";
                break;
            case 2:
                path = (char*)"assets/grass.png";
                break;
            default:
                break;
        }
    }

    void init() override
    {
        entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, Vector2D(1, 1));
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }

private:


};