#pragma once

#include "./GameObject.h"

class Character : public GameObject
{
public:
    Character(int _width, int _height, Vector2 pos, std::string _tag)
        : GameObject(_width, _height, pos, _tag) // Call the base class constructor
    {
        // Additional initialization for Character if needed
    }

private:

};

