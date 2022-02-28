#pragma once
#include "PhysicsClasses.h"
#include <SDL.h>

extern SDL_Renderer* renderer;

class Blocks {

	public:
		Blocks(const Blocks&) = delete;

		static Blocks& Get() {

			static Blocks instance;
			return instance;

		}

		gameObject GetCrystal() { return crystal; }

	private:

		gameObject crystal;

		Blocks() {

			crystal = *new gameObject("crystal", *new Vector2<float>(60, 60), "Images/Rock.png", renderer);

		}


};