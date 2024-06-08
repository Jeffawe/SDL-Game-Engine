#pragma once
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <chrono>
#include <memory>
#include <typeinfo>
#include <algorithm>
#include <unordered_map>
#include <typeindex>
#include "../EngineValues.h"
#include "Component.h"

class GameObject
{
public:
    GameObject(int _width, int _height, Vector2 pos, std::string _tag, int _zIndex);
    ~GameObject() = default;

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

        // Check if the component already exists
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            // Component already exists, return the existing instance
            return *static_cast<T*>(it->second.get());
        }

        // Create a new component
        std::unique_ptr<Component> comp = std::make_unique<T>(std::forward<TArgs>(args)...);
        comp->owner = this;
        components.emplace(typeid(T), std::move(comp));
        return *static_cast<T*>(components.at(typeid(T)).get());
    }

    template<typename T>
    T* getComponent() {
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            return static_cast<T*>(it->second.get());
        }

        return nullptr;
    }

    //Function runs once when the game starts
    int start();

    //Function runs at each update
    void update();

    void render();

    void close();

    Vector2 getPos();

    Vector2 position;

    int getWidth();

    int getHeight();

    SDL_Rect destRect;
    std::string tag;
    int zIndex;

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

protected:
    int width;
    int height;
};

