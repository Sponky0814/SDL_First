#pragma once
#include "PhysicsClasses.h"
#include <SDL.h>

extern SDL_Renderer* renderer;

//Singleton
class Textures {

	public:

		Textures(const Textures&) = delete;

		static Textures& Get() {

			static Textures instance;
			return instance;

		}

		SDL_Texture* GetCrystal() { return crystal; }

	private:

		SDL_Texture* crystal;

		Textures() {

			crystal = LoadTexture("Images/Rock.png", renderer);

		}


};