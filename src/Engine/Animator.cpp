#include "Animator.h"
#include "GameObject.h"

Animator::Animator(SDL_Renderer* _renderer, int _frameDelay)
{
	gRenderer = _renderer;
	currentState = nullptr;
	frameDelay = 1000 / _frameDelay;
}

void Animator::CreateAnimationState(std::vector<SDL_Texture*> textures, std::string name)
{
	// Construct AnimationState object using std::make_shared
	auto animationStatePtr = std::make_shared<AnimationState>(textures, name, frameDelay);

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
		AnimationState& animState = *pair.second;   // Get the AnimationState object

		for (SDL_Texture* texture : animState.animation.textures) {
			SDL_DestroyTexture(texture);  // Destroy each texture
		}

		animState.animation.textures.clear();
	}

	states.clear();
}

void Animator::SetInitialState(std::string state)
{
	auto it = states.find(state);
	if (it != states.end()) {
		currentState = it->second;
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
}

std::shared_ptr<AnimationState> Animator::FindAnimationState(std::string name)
{
	auto it = states.find(name);
	if (it != states.end()) {
		return it->second;
	}
	return nullptr;
}

void Animator::close()
{
	CleanAnimations();
}

AnimationState::AnimationState(std::vector<SDL_Texture*> textures, std::string name, int _frameDelay)
{
	animation.textures = textures;
	animation.name = name;
	playerFrame = 0;
	frameDelay = _frameDelay;
	lastFrameTime = 0;
}

void AnimationState::addTransition(std::string event, std::string nextState)
{
	transitions[event] = nextState;
}

void AnimationState::PlayAnimation(SDL_Renderer* renderer, SDL_Rect* destRect)
{
	if (playerFrame >= animation.textures.size()) playerFrame = 0;
	Uint32 currentTime = SDL_GetTicks();
	if (currentTime - lastFrameTime >= frameDelay) {
		playerFrame = (playerFrame + 1) % animation.textures.size();
		lastFrameTime = currentTime;
	}

	SDL_RenderCopy(renderer, animation.textures[playerFrame], NULL, destRect);
}
