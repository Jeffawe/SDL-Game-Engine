#pragma once

#include "Engine\GameObject.h"
#include "Engine\SpriteComponent.h"
#include "Engine\TextureManager.h"
#include "Engine\Character.h"
#include "Engine\Animator.h"
#include "Engine\ColliderComponent.h"
#include "EngineValues.h"
#include "Game/InputManager.h"
#include "Engine/TransformComponent.h"
#include "Engine/Camera.h"
#include "Engine/Tilemap.h"

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <unordered_map>
#include <map>
#include <type_traits>
#include <filesystem>