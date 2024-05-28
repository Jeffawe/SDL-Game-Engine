#include "GameObject.h"
#include <iostream> 

GameObject::GameObject(int _width, int _height, int _x, int _y)
{
    width = _width;
    height = _height;

    x = _x;
    y = _y;
}

int GameObject::start()
{
    return 0;
}

void GameObject::update()
{
    if (components.empty()) return;

    for (const auto& pair : components) {
        // Access the value (unique_ptr<Component>)
        if (pair.second) {
            const std::unique_ptr<Component>& componentPtr = pair.second;

            componentPtr->update();
        }
    }
}

void GameObject::render()
{
    if (components.empty()) return;

    for (const auto& pair : components) {
        // Access the value (unique_ptr<Component>)
        const std::unique_ptr<Component>& componentPtr = pair.second;

        componentPtr->render();
    }
}

void GameObject::close()
{

}

int GameObject::getX()
{
    return x;
}

int GameObject::getY()
{
    return y;
}

int GameObject::getWidth()
{
    return width;
}

int GameObject::getHeight()
{
    return height;
}


