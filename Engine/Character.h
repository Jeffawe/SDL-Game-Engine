#pragma once
#include "GameObject.h"

class Character : public GameObject
{
public:
    Character(int _width, int _height, Vector2 pos, std::string tag, int zIndex)
        : GameObject(_width, _height, pos, tag, zIndex){
        // Initialization specific to Character
    }

private:

};

