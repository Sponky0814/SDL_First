#pragma once
#include <iostream>
#include "PhysicsClasses.h"

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

		Transform BlockMap[256][128];

		DyArray<Cell> CellArray;

		Level() {}

		~Level() {}

		Level(int* tM, int x, int y) { TileMap = tM; Resolution.x = x; Resolution.y = y; }

};
