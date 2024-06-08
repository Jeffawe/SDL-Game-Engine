#include "GameObject.h"
#include <iostream> 

GameObject::GameObject(int _width, int _height, Vector2 pos, std::string _tag, int _zIndex)
{
    width = _width;
    height = _height;

    position = pos;
    tag = _tag;
    zIndex = _zIndex;

    destRect = { position.x, position.y, width, height };
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

Vector2 GameObject::getPos()
{
    return position;
}

int GameObject::getWidth()
{
    return width;
}

int GameObject::getHeight()
{
    return height;
}


