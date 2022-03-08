#pragma once
#include <iostream>
#include "PhysicsClasses.h"
#include "Log.h"

class Cell {

	public:
		int type = NULL;
		Transform cellTransform;

		Cell() {}

		Cell(int t, Transform ct) { type = t; cellTransform = ct; }

		Cell operator=(const Cell& other) const { return other; }

};

class Level {

	private:

		int size;

	public:

		Transform BlockMap[256][128];

		Cell* cellArray;

		Level() {}

		~Level() {}

		Level(int* TileMap, int resX, int resY) {


		}

		int GetCellArraySize() { return size; }

};
