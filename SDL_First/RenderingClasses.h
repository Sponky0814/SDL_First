#pragma once
#include "PhysicsClasses.h"
#include <SDL.h>

extern SDL_Renderer* renderer;

//Singleton that returns textures
class Textures {

	public:

		Textures(const Textures&) = delete;

		static Textures& Get() {

			static Textures instance;
			return instance;

		}

		SDL_Texture* GetCrystal() { return crystal; }
		SDL_Texture* GetBlue() { return blue; }
		SDL_Texture* GetRed() { return red; }
		SDL_Texture* GetGreen() { return green; }

	private:

		SDL_Texture* crystal;
		SDL_Texture* red;
		SDL_Texture* blue;
		SDL_Texture* green;

		Textures() {

			crystal = LoadTexture("Images/Rock.png", renderer);
			red = LoadTexture("Images/Red.png", renderer);
			green = LoadTexture("Images/Green.png", renderer);
			blue = LoadTexture("Images/Blue.png", renderer);

		}


};