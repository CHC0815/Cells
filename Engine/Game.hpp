#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <vector>
#include "LuaHandler.hpp"

class ColliderComponent;

class Game{

public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running(){
        return isRunning;
    }

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;
    static LuaHandler* luaHandler;

private:
    int count = 0;
    bool isRunning;
    SDL_Window* window;
};
