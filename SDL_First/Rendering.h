#pragma once
#include <iostream>
#include "PhysicsClasses.h"
#include <SDL.h>
#include "Log.h"

SDL_Texture* LoadTexture(const char* file, SDL_Renderer* Renderer) {

	SDL_Surface* LoadedSurface = IMG_Load(file);

	SDL_Texture* loadingTexture;

	loadingTexture = SDL_CreateTextureFromSurface(Renderer, LoadedSurface);

	SDL_FreeSurface(LoadedSurface);

	if (loadingTexture == nullptr) {
		Error(SDL_GetError());
	}

	return loadingTexture;

}
