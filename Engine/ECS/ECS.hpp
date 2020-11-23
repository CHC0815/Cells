#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <string>

#include "../LuaHandler.hpp"

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;
using EntityId = std::size_t;

inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}


class Component{
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component(){}
};

class Entity{
public:

    explicit Entity(EntityId id)
    {
        this->id = id;
        this->name = std::to_string(id);
    }

    void update()
    {
        for(auto& c : components) c->update();
    }

    void draw()
    {
        for(auto& c : components) c->draw();
    }

    bool isActive() const { return active; }
    void destroy() { active = false; }

    EntityId getId() const { return this->id; }
    const std::string& getName() const  { return name; }
    void setName(const std::string& n) { name = n; }

    template <typename T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr { c };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

private:
    EntityId id;
    std::string name;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet; 
};

class Manager
{
private:
    std::unordered_map<EntityId, std::unique_ptr<Entity>> entities;
    EntityId idCounter;

public:
    Manager() : idCounter(0) {}

    void update()
    {
        for(auto const& [key, val] : entities)
        {
            val->update();
        }
    }
    void draw()
    {
        for(auto const& [key, val] : entities)
        {
            val->draw();
        }
    }

    Entity& createEntity()
    {
        auto id = idCounter;
        ++idCounter;

        auto inserted = entities.emplace(id, std::make_unique<Entity>(id));
        auto it = inserted.first;
        auto& e = *it->second;
        LuaHandler::lua["createHandle"](e);
        return e;
    }

    void removeEntity(EntityId id)
    {
        LuaHandler::lua["onEntityRemoved"](id);
        entities.erase(id);
    }
};
