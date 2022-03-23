#pragma once
#include "PhysicsClasses.h"
#include <SDL.h>

struct Texture {

	const char* name = "";
	SDL_Texture* Img;

};

//Singleton that returns textures
class Textures {

private:

	inline static FreeArray<Texture> TextureArray = FreeArray<Texture>();

	Textures(const Textures&) = delete;

	Textures() {}

public:


	static Textures& Get() {

		static Textures instance;
		return instance;

	}

	static void AddTexture(const char* name, const char* path, SDL_Renderer* renderer) {

		SDL_Surface* LoadedSurface = IMG_Load(path);

		SDL_Texture* loadingTexture;

		loadingTexture = SDL_CreateTextureFromSurface(Renderer, LoadedSurface);
		
		Texture texture { name, loadingTexture };

		SDL_FreeSurface(LoadedSurface);

		if (loadingTexture == nullptr) {
			Error(SDL_GetError(), false);
		}

		for (int i = 0; i < TextureArray.range(); i++) {

			if (TextureArray[i].name == name) {

				Error("A texture with the same name already exists", 0);

				return;

			}

		}

		TextureArray.insert(texture);

		return;

	}

	static SDL_Texture* GetTexture(const char* name) {

		for (int i = 0; i < TextureArray.range(); i++) {

			if (TextureArray[i].name == name) {

				return TextureArray[i].Img;

			}

		}

		Error("Couldn't find texture", 1);

		return *new SDL_Texture*;

	}

};
