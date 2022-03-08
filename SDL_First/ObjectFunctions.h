#pragma once
#include <SDL_image.h>
#include "Log.h"
#include "PhysicsClasses.h"
#include "Mmath.h"

SDL_Rect* ToRect(const Transform t) {

	SDL_Rect* rect = new SDL_Rect;
	rect->x = (int)t.position.x;
	rect->y = (int)t.position.y;
	rect->w = (int)t.size.x;
	rect->h = (int)t.size.y;

	return rect;

}

void Draw(gameObject gO, SDL_Renderer* Renderer, SDL_Rect Resolution) {

	if (gO.texture == nullptr)
		Error("Empty texture");

	SDL_RenderCopy(Renderer, gO.texture, &Resolution, ToRect(gO.transform));

}

gameObject GetCollisions(gameObject Obj, Level level) {

    Transform MainBorders[4];

	//a
	MainBorders[0].position.x = Obj.transform.position.x - 1;
	MainBorders[0].position.y = Obj.transform.position.y;
	MainBorders[0].size.y = Obj.transform.size.y;

	//b
	MainBorders[1].position.x = Obj.transform.position.x;
	MainBorders[1].position.y = Obj.transform.position.y + Obj.transform.size.y;
	MainBorders[1].size.x = Obj.transform.size.x;

	//c
	MainBorders[2].position.x = Obj.transform.position.x + Obj.transform.size.x;
	MainBorders[2].position.y = Obj.transform.position.y;
	MainBorders[2].size.y = Obj.transform.size.y;

	//d
	MainBorders[3].position = Obj.transform.position;
	MainBorders[3].size.x = Obj.transform.size.x;

	Obj.collider = new Collider;

	int x0 = (int)ceil(Obj.transform.position.x / 128);

	int x1 = (int)ceil((Obj.transform.position.x + Obj.transform.size.x) / 128);

	int y0 = 16 * (int)ceil(Obj.transform.position.y / 128);

	int y1 = 16 * (int)ceil((Obj.transform.position.y + Obj.transform.size.y) / 128);

	//Upper left
	int A = x0 + y0;
	
	//Lower left
	int B = x0 + y1;

	//Lower right
	int C = x1 + y1;

	//Upper right
	int D = x1 + y0;

	for (int i = 0; i < 128; i++) {

		if (A > 256)
			A = 256;

		if (level.BlockMap[A][i] != *new Transform(0,0,0,0) &&
			level.BlockMap[A][i].position.x < MainBorders[1].position.x &&
			level.BlockMap[A][i].position.x + level.BlockMap[A][i].size.x < MainBorders[1].position.x &&
			level.BlockMap[A][i].position.y - 1 == MainBorders[1].position.y) {

			Obj.collider.b = true;
			Obj.transform.position.y = level.BlockMap[A][i].position.y - 1;
			Obj.velocity.y = 0;

		}

	}

	return Obj;

}
