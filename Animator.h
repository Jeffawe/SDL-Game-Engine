#pragma once
#include <SDL.h>
#include <vector>
#include <chrono>
#include <string>

enum class AnimationState {
	Idle,
	Moving,
	Attack
};

enum class Direction {
	Left,
	Right
};

struct AnimationType {
	char name; 
	AnimationState animationState;
	std::vector<SDL_Texture*> textures;

	// Equality comparison operator
	bool operator==(const AnimationType& other) const {
		// Compare 'name' and 'textures' for equality
		return name == other.name && textures == other.textures;
	}
};

class Animator
{
public:
	Animator(SDL_Renderer* gRenderer );
	bool PlayAnimationClip(AnimationType animationType, SDL_Rect* playerRect, Direction direction);
	bool PlayAnimation(SDL_Rect* playerRect, Direction direction);
	void CreateAnimationType(char name, AnimationState _animationState, std::vector<SDL_Texture*> texture);
	void CleanAnimations();

	AnimationState movementState;

private:
	AnimationType FindAnimationType(AnimationState finlAnimationState);
	std::vector<AnimationType*> animationStates;

	// Player animation frame index
	int playerFrame = 0;
	SDL_Renderer* gRenderer;

	AnimationType emptyAnimationType;
};

