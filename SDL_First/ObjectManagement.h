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

Transform* GetBorders(gameObject tempObject) {

	Transform ColZone[4]{};

	//a
	ColZone[0].position.x = tempObject.transform.position.x - 1;
	ColZone[0].position.y = tempObject.transform.position.y;
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

Collider GetCollisions(gameObject Obj, Transform BlockMap[256][128]) {

    Transform* MainBorders = GetBorders(Obj);

	bool a, b, c, d;

	int x0 = (int)ceil(Obj.transform.position.x / 128);

	int x1 = (int)ceil((Obj.transform.position.x + Obj.transform.size.x) / 128);

	int y0 = 32 * (int)ceil(Obj.transform.position.y / 128);

	int y1 = 32 * (int)ceil((Obj.transform.position.y + Obj.transform.size.y) / 128);

	//Upper left
	int A = x0 + y0;
	
	//Lower left
	int B = x0 + y1;

	//Lower right
	int C = x1 + y1;

	//Upper right
	int D = x1 + y0;

	for (int i = 0; i < 128; i++) {

		if (BlockMap[A][i] != new Transform(0,0,0,0)) {

			//if ()

		}

	}

	return *new Collider();

}