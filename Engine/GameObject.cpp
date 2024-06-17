#include "GameObject.h"
#include "./Camera.h"


GameObject::GameObject(int _width, int _height, Vector2 pos, std::string _tag)
{
    width = _width;
    height = _height;
    position = pos;
    tag = _tag;
    ChangeDestRect();
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
            pair.second->update(); // Dereference and call update() directly
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
    for (const auto& pair : components) {
        // Access the value (unique_ptr<Component>)
        const std::unique_ptr<Component>& componentPtr = pair.second;

        componentPtr->close();
    }

    components.clear();
}

Vector2 GameObject::getPos() const
{
    return position;
}

int GameObject::getWidth() const
{
    return width;
}

int GameObject::getHeight() const
{
    return height;
}

void GameObject::ChangeDestRect()
{
    Camera& camera = Camera::getInstance();
    Vector2 pos = camera.worldToScreen(position, tag);
    destRect = { pos.x, pos.y, width, height };
}


