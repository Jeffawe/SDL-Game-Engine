#pragma once

#include "Game/Game.h"

class Snake : public Game
{
public:
	Snake() = default;

	int Start() override;

	int Update() override;
};
