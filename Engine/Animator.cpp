#include "Animator.h"
#include <SDL.h>

Animator::Animator(SDL_Renderer* _renderer)
{
	gRenderer = _renderer;
	movementState = AnimationState::Idle;
}

bool Animator::PlayAnimationClip(AnimationType animationType, SDL_Rect* playerRect, Direction direction)
{
	if (animationType == emptyAnimationType) {
		return false;
	}

	if (playerFrame >= animationType.textures.size()) playerFrame = 0;

	if (direction == Direction::Left) {
		SDL_RenderCopyEx(gRenderer, animationType.textures[playerFrame], NULL, playerRect, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopy(gRenderer, animationType.textures[playerFrame], NULL, playerRect);
	}
	
	playerFrame = (playerFrame + 1) % animationType.textures.size();
	return true;
}

bool Animator::PlayAnimation(SDL_Rect* playerRect, Direction direction)
{
	AnimationType animationType = FindAnimationType(movementState);

	if (animationType == emptyAnimationType) {
		return false;
	}

	return PlayAnimationClip(animationType, playerRect, direction);
}

void Animator::CreateAnimationType(char _name, AnimationState _animationState, std::vector<SDL_Texture*> _textures)
{
	AnimationType* animationType = new AnimationType();
	animationType->name = _name;
	animationType->animationState = _animationState;
	animationType->textures = _textures;
	animationStates.push_back(animationType);
}

void Animator::CleanAnimations()
{
	// Destroy player textures
	for (AnimationType* animationType : animationStates) {
		for (SDL_Texture* texture : animationType->textures) {
			SDL_DestroyTexture(texture);
		}
	}
}

AnimationType Animator::FindAnimationType(AnimationState finalAnimationState)
{
	for (AnimationType* animationType : animationStates) {
		if (animationType->animationState == finalAnimationState) {
			return *animationType;
		}
	}

	printf("No Object Found");
	return emptyAnimationType;
}
