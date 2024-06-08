#pragma once
#include "../Engine.h"
#include "Component.h"


struct Animation {
	std::string name;
	std::vector<SDL_Texture*> textures;

	// Equality comparison operator
	bool operator==(const Animation& other) const {
		// Compare 'name' and 'textures' for equality
		return name == other.name && textures == other.textures;
	}
};

class AnimationState {
public:
	AnimationState() = default;

	AnimationState(std::vector<SDL_Texture*> textures, std::string name);

	Animation animation;
	std::unordered_map<std::string, std::string> transitions;

	void addTransition(std::string event, std::string nextState);

	void PlayAnimation(SDL_Renderer* renderer, SDL_Rect* destRect);
};

/// @brief A component that handles animation.
/// @param Renderer Takes in the SDL Renderer.
class Animator : public Component
{
public:
	Animator( SDL_Renderer* gRenderer );

	/// @brief Creates an Animation.
	/// @param textures Array of textures that make up the animation.
	/// @param name Name of the Animation
	void CreateAnimationState(std::vector<SDL_Texture*> textures, std::string name);

	/// @brief Adds a new transition
	/// @param fromState Name of the Animation that has the transition.
	/// @param event Transtition Name.
	/// @param toState Name of the Animation that the transition moves to.
	void addTransition(std::string fromState, std::string event, std::string toState);

	void CleanAnimations();

	void SetInitialState(std::string state);

	/// @brief Changes the Animation being played
	/// @param event Transition Name.
	void handleEvent(std::string event);

	void update() override;


	std::shared_ptr<AnimationState> getCurrentState() const
	{
		return currentState;
	}

	//Called on render
	void render() override {}


	int value;

private:
	std::unordered_map<std::string, std::shared_ptr<AnimationState>> states;

	std::shared_ptr<AnimationState> FindAnimationState(std::string name);

	// Player animation frame index
	SDL_Renderer* gRenderer;

	std::shared_ptr<AnimationState> currentState;
};

