#pragma once
#include <SDL_image.h>
#include "Log.h"
#include "PhysicsClasses.h"
#include "Mmath.h"

//Turns a transform into a SDL_Rect
SDL_Rect* ToRect(const Transform t) {

	SDL_Rect* rect = new SDL_Rect;
	rect->x = (int)t.position.x;
	rect->y = (int)t.position.y;
	rect->w = (int)t.size.x;
	rect->h = (int)t.size.y;

	return rect;

}

//Draws a gameObject
void Draw(gameObject gO, SDL_Renderer* Renderer, SDL_Rect Resolution) {

	if (gO.texture == nullptr)
		Error("Empty texture", false);

	SDL_RenderCopy(Renderer, gO.texture, &Resolution, ToRect(gO.transform));

}

//Checks if two transforms collide
Vector4<bool> checkCollision(Transform A, Transform B) {

	Vector4<bool> Vec;

	//The sides of the rectangles
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	//Calculate the sides of Transform A
	leftA = A.position.x;
	rightA = A.position.x + A.size.x;
	topA = A.position.y;
	bottomA = A.position.y + A.size.y;

	//Calculate the sides of Transform B
	leftB = B.position.x;
	rightB = B.position.x + B.size.x;
	topB = B.position.y;
	bottomB = B.position.y + B.size.y;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
		Vec.b = true;

	if (topA >= bottomB)
		Vec.d = true;

	if (rightA <= leftB)
		Vec.c = true;

	if (leftA >= rightB)
		Vec.a = true;

	//If none of the sides from A are outside B
	return Vec;

}

//Calculates collisions
gameObject GetCollisions(gameObject Obj, Level level) {

	Obj.collider = *new Vector4<bool>;

	int x0 = (int)ceil(ceil(Obj.transform.position.x) / 128);

	int x1 = (int)ceil((ceil(Obj.transform.position.x) + ceil(Obj.transform.size.x)) / 128);

	int y0 = (int)(32 * ceil(ceil(Obj.transform.position.y) / 128));

	int y1 = (int)(32 * ceil((ceil(Obj.transform.position.y) + ceil(Obj.transform.size.y)) / 128));

	//Upper left
	int A = x0 + y0;
	
	if (A > 1023)
		A = 1023;

	//Lower left
	int B = x0 + y1;

	if (B > 1023)
		B = 1023;

	//Lower right
	int C = x1 + y1;

	if (C > 1023)
		C = 1023;

	//Upper right
	int D = x1 + y0;

	if (D > 1023)
		D = 1023;

	for (int i = level.BlockMap[A].range() - 1; i >= 0; i--) {

		Obj.collider = checkCollision(Obj.transform, level.BlockMap[A][i]);

		if (Obj.collider.a) {

			Obj.velocity.x = 0;
			Obj.transform.position.x = level.BlockMap[A][i].position.x + level.BlockMap[A][i].size.x + 1;

		}

		if (Obj.collider.b) {

			Obj.velocity.y = 0;
			Obj.transform.position.y = level.BlockMap[A][i].position.y + 1;

		}

		if (Obj.collider.c) {

			Obj.velocity.x = 0;
			Obj.transform.position.x = level.BlockMap[A][i].position.x - Obj.transform.size.x - 1;

		}

		if (Obj.collider.d) {

			Obj.velocity.y = 0;
			Obj.transform.position.y = level.BlockMap[A][i].position.y - level.BlockMap[A][i].size.y - 1;

		}

	}

	if (B != A) {

		for (int j = level.BlockMap[B].range() - 1; j >= 0; j--) {

			Obj.collider = checkCollision(Obj.transform, level.BlockMap[B][j]);

			if (Obj.collider.a) {

				Obj.velocity.x = 0;
				Obj.transform.position.x = level.BlockMap[B][j].position.x + level.BlockMap[B][j].size.x + 1;

			}

			if (Obj.collider.b) {

				Obj.velocity.y = 0;
				Obj.transform.position.y = level.BlockMap[B][j].position.y + 1;

			}

			if (Obj.collider.c) {

				Obj.velocity.x = 0;
				Obj.transform.position.x = level.BlockMap[B][j].position.x - Obj.transform.size.x - 1;

			}

			if (Obj.collider.d) {

				Obj.velocity.y = 0;
				Obj.transform.position.y = level.BlockMap[B][j].position.y - level.BlockMap[B][j].size.y - 1;

			}

		}

	}

	if (C != B && C != A) {

		for (int k = level.BlockMap[C].range() - 1; k >= 0; k--) {

			Obj.collider = checkCollision(Obj.transform, level.BlockMap[C][k]);

			if (Obj.collider.a) {

				Obj.velocity.x = 0;
				Obj.transform.position.x = level.BlockMap[C][k].position.x + level.BlockMap[C][k].size.x + 1;

			}

			if (Obj.collider.b) {

				Obj.velocity.y = 0;
				Obj.transform.position.y = level.BlockMap[C][k].position.y + 1;

			}

			if (Obj.collider.c) {

				Obj.velocity.x = 0;
				Obj.transform.position.x = level.BlockMap[C][k].position.x - Obj.transform.size.x - 1;

			}

			if (Obj.collider.d) {

				Obj.velocity.y = 0;
				Obj.transform.position.y = level.BlockMap[C][k].position.y - level.BlockMap[C][k].size.y - 1;

			}

		}

	}

	if (D != B && D != A && D != C) {

		for (int l = level.BlockMap[D].range() - 1; l >= 0; l--) {

			Obj.collider = checkCollision(Obj.transform, level.BlockMap[D][l]);

			if (Obj.collider.a) {

				Obj.velocity.x = 0;
				Obj.transform.position.x = level.BlockMap[D][l].position.x + level.BlockMap[D][l].size.x + 1;

			}

			if (Obj.collider.b) {

				Obj.velocity.y = 0;
				Obj.transform.position.y = level.BlockMap[D][l].position.y + 1;

			}

			if (Obj.collider.c) {

				Obj.velocity.x = 0;
				Obj.transform.position.x = level.BlockMap[D][l].position.x - Obj.transform.size.x - 1;
				
			}

			if (Obj.collider.d) {

				Obj.velocity.y = 0;
				Obj.transform.position.y = level.BlockMap[D][l].position.y - level.BlockMap[D][l].size.y - 1;
				
			}

		}

	}

	return Obj;

}
