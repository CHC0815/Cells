#pragma once
#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component
{

public:
    Vector2D position;
    Vector2D velocity;
    Vector2D scale;

    int height = 32;
    int width = 32;

    float speed = 1.0f;

    TransformComponent()
    {
        position.x = 0.0f;
        position.y = 0.0f;
    }
    TransformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    TransformComponent(Vector2D sc)
    {
        position.x = 0.0f;
        position.y = 0.0f;
        scale = sc;
    }

    TransformComponent(float x, float y, int w, int h, Vector2D sc)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override
    {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};