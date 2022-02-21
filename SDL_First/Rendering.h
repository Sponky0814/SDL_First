#pragma once
#include <iostream>
#include <SDL.h>
#include "Log.h"

SDL_Texture* LoadTexture(const char* file, SDL_Renderer* Renderer) {

	SDL_Surface* LoadedSurface = IMG_Load(file);

	SDL_Texture* loadingTexture{};

	SDL_DestroyTexture(loadingTexture);

	loadingTexture = SDL_CreateTextureFromSurface(Renderer, LoadedSurface);

	SDL_FreeSurface(LoadedSurface);

	if (loadingTexture == nullptr) {
		Error("Empty texture");
	}

	return loadingTexture;

}