#pragma once
#include <iostream>
#include "PhysicsClasses.h"

extern SDL_Renderer* renderer;

gameObject crystal("crystal", {60, 60}, "Images/Rock.png", renderer);

class Cell {

	public:
		int type = NULL;
		Transform cellTransform;

		Cell() {}

		Cell(int t, Transform ct) { type = t; cellTransform = ct; }

};

class Level {

public:
	int* TileMap = NULL;
	Vector2<int> Resolution;

	DyArray<Cell> CellArray;

	Level() {}

	~Level() {}

	Level(int* tM, Vector2<int> r) { TileMap = tM; Resolution = r; }

};