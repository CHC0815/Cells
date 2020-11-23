#include "LuaHandler.hpp"
#include "ECS/ECS.hpp"

sol::state LuaHandler::lua;

void LuaHandler::init(std::string path)
{
    lua.open_libraries(sol::lib::base, sol::lib::package);

    lua.new_usertype<Entity>("Entity",
    "getName", &Entity::getName,
    "setName", &Entity::setName,
    "getId", &Entity::getId);
    //"addComponent", &Entity::addComponent,
    //"hasComponent", &Entity::hasComponent);


    lua.do_file(path.c_str());
}