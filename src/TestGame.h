#pragma once

#include "Game/Game.h"

class TestGame : public Game
{
public:
	TestGame() = default;

	int Start() override;

	int Update() override;
};

