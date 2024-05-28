#pragma once
#include <string>
#include <typeinfo>

class GameObject;

class Component {
public:
    GameObject* owner;

    virtual ~Component() = default;

    virtual void update() = 0;
    virtual void render() = 0;

    template<typename T>
    bool is() {
        return typeid(T).hash_code() == typeid(*this).hash_code();
    }
};

