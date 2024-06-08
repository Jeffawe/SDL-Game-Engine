#include "Animator.h"

Animator::Animator(SDL_Renderer* _renderer)
{
	gRenderer = _renderer;
	currentState = nullptr;
}

void Animator::CreateAnimationState(std::vector<SDL_Texture*> textures, std::string name)
{
	// Construct AnimationState object using std::make_shared
	auto animationStatePtr = std::make_shared<AnimationState>(textures, name);

	// Emplace the shared pointer into the map
	states.emplace(name, animationStatePtr);
}

void Animator::addTransition(std::string fromState, std::string event, std::string toState)
{
	if (states.find(fromState) != states.end() && states.find(toState) != states.end()) {
		states[fromState]->addTransition(event, toState);
	}
}

void Animator::CleanAnimations()
{
	for (const auto& pair : states) {
		const std::string& stateName = pair.first;  // Get the key
		AnimationState& animState = *pair.second;   // Get the AnimationState object

		for (SDL_Texture* texture : animState.animation.textures) {
			SDL_DestroyTexture(texture);  // Destroy each texture
		}
	}
}

void Animator::SetInitialState(std::string state)
{
	auto it = states.find(state);
	if (it != states.end()) {
		currentState = it->second;
		value = 5;
		printf("Set Current State");
	}
	else {
		printf("Cannot Find a state");
	}
}

void Animator::handleEvent(std::string event)
{
	if (currentState && currentState->transitions.find(event) != currentState->transitions.end()) {
		auto nextState = FindAnimationState(currentState->transitions[event]);
		if (nextState != nullptr) {
			currentState = nextState;
		}
	}
}

void Animator::update()
{
	if (owner != nullptr && getCurrentState() != nullptr) {
		currentState->PlayAnimation(gRenderer, &owner->destRect);
	}

	value = value;
}

std::shared_ptr<AnimationState> Animator::FindAnimationState(std::string name)
{
	auto it = states.find(name);
	if (it != states.end()) {
		return it->second;
	}
	return nullptr;
}

AnimationState::AnimationState(std::vector<SDL_Texture*> textures, std::string name)
{
	animation.textures = textures;
	animation.name = name;

}

void AnimationState::addTransition(std::string event, std::string nextState)
{
	transitions[event] = nextState;
}

void AnimationState::PlayAnimation(SDL_Renderer* renderer, SDL_Rect* destRect)
{
	for (auto texture : animation.textures)
	{
		SDL_RenderCopy(renderer, texture, NULL, destRect);
	}
}
