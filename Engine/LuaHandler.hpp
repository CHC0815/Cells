#pragma once
#include <string>
#include <sol/sol.hpp>

class LuaHandler
{
public:
    static sol::state lua;
    void init(std::string path);
    LuaHandler();
    ~LuaHandler();
};