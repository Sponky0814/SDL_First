#pragma once
#include <iostream>
#include "PhysicsClasses.h"
#include <SDL.h>
#include "Log.h"

class Textures {

	public:
		Textures(const Textures&) = delete;

		static Textures& Get() {

			static Textures instance;
			return instance;

		}

		static gameObject GetCrystal() {}

	private:

		gameObject crystal;

		Textures() {

			//crystal = *new gameObject("crystal", *new Vector2<float>(60, 60), "Images/Rock.png", renderer);

		}


};


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
