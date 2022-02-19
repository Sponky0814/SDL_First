#pragma once
#include <SDL_image.h>
#include "Log.h"
#include "Mmath.h"

extern SDL_Renderer* renderer;

extern SDL_Rect Screen;

class Collider {

	public:
		bool a, b, c, d;

		Collider() {
			a = false; b = false; c = false; d = false;
		}

};

class Transform {

	public:
		Vector2<float> position;
		Vector2<float> size;

		Transform() {}

		Transform(float x, float y, float w, float h) {
			position = new Vector2<float>(x, y); size = new Vector2<float>(w, h);
		}

		bool operator==(Transform* other) {

			if (position.x == other->position.x && position.y == other->position.y && size.x == other->size.x && size.y == other->size.y)
				return true;
			else
				return false;

		}

};

Transform BlockMap[256][128];

class RigidBody {

	public:
		Vector2<float> velocity;

};

class gameObject {

	public:
		Transform transform{};
		Collider collider{};
		RigidBody rigidBody{};
		SDL_Texture* texture{};

		const char* name = "Unknown";

		gameObject() {}

};

//####################
//Function definitions
//####################

SDL_Texture* LoadTexture(const char* file) {

	SDL_Surface* LoadedSurface = IMG_Load(file);

	SDL_Texture* loadingTexture{};

	SDL_DestroyTexture(loadingTexture);

	loadingTexture = SDL_CreateTextureFromSurface(renderer, LoadedSurface);

	SDL_FreeSurface(LoadedSurface);

	if (loadingTexture == nullptr) {
		Error("Empty texture");
	}

	return loadingTexture;

}

SDL_Rect* ToRect(Transform t) {

	SDL_Rect* rect = new SDL_Rect;
	rect->x = (int)t.position.x;
	rect->y = (int)t.position.y;
	rect->w = (int)t.size.x;
	rect->h = (int)t.size.y;

	return rect;

}

void Draw(gameObject gO) {

	if (gO.texture == nullptr)
		Error("Empty texture");

	SDL_RenderCopy(renderer, gO.texture, &Screen, ToRect(gO.transform));

}

Transform* GetBorders(gameObject tempObject) {

	Transform ColZone[4]{};

	//a
	ColZone[0].position = tempObject.transform.position; 
	ColZone[0].size.y = tempObject.transform.size.y;

	//b
	ColZone[1].position.x = tempObject.transform.position.x;
	ColZone[1].position.y = tempObject.transform.position.y + tempObject.transform.size.y;
	ColZone[1].size.x = tempObject.transform.size.x;

	//c
	ColZone[2].position.x = tempObject.transform.position.x + tempObject.transform.size.x;
	ColZone[2].position.y = tempObject.transform.position.y;
	ColZone[2].size.y = tempObject.transform.size.y;

	//d
	ColZone[3].position = tempObject.transform.position;
	ColZone[3].size.x = tempObject.transform.size.x;

	return ColZone;

}

void CheckCollision(gameObject& Obj) {

    Transform* MainBorders = GetBorders(Obj);

	

}