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

};

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

DyArray<Transform> TrArray;

DyArray<Transform> BlockMap[128];

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

float* GetBorders(gameObject tempObject) {

	static float ColZone[4]{};
	ColZone[0] = (float)tempObject.transform.position.x;
	ColZone[1] = (float)tempObject.transform.position.x + tempObject.transform.size.x;
	ColZone[2] = (float)tempObject.transform.position.y;
	ColZone[3] = (float)tempObject.transform.position.y - tempObject.transform.size.y;

	return ColZone;

}

void CheckCollision(gameObject& Obj) {

    float MainBorders[3]{};

	for (int i = 0; i < 4; i++) {

		if (i == 0 || i == 2)
			MainBorders[i] = GetBorders(Obj)[i] - 1;
		else
			MainBorders[i] = GetBorders(Obj)[i] + 1;

	}

	if (MainBorders[2] > Screen.h - Obj.transform.size.y)
		Obj.collider.b = true;
	else
		Obj.collider.b = false;

	if (MainBorders[0] < 0) {

		Obj.collider.a = true;

		Obj.transform.position.x = 0;

	}
	else
		Obj.collider.a = false;

	if (MainBorders[1] > Screen.w) {

		Obj.collider.c = true;

		Obj.transform.position.x = Screen.w - Obj.transform.size.x;

	}
	else
		Obj.collider.c = false;



}