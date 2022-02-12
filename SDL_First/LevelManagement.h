#pragma once
#include "Mmath.h"
#include "ObjectManagement.h"
#include "Log.h"

extern SDL_Renderer* renderer;

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

		gameObject crystal;

		DyArray<Cell> CellArray;

		Level() {
			
			crystal.name = "Crystal";
			crystal.texture = LoadTexture("Rock.png");
			crystal.transform.size = { 60, 60 };

		}

		~Level() {}

		Level(int* tM, Vector2<int> r) {
			TileMap = tM; Resolution = r;

			crystal.name = "Crystal";
			crystal.texture = LoadTexture("Rock.png");
			crystal.transform.size = { 60, 60 };

		}

};

	int CellId = 0;

	gameObject Block;
	gameObject Line;

//####################
//Function definitions
//####################

void InisializeLevel(Level* level) {

	Block.transform.size = { 60, 60 };
	CellId = NULL;
	level->CellArray.members = new Cell;

	for (int row = 0; row < level->Resolution.y; row++) {

		Block.transform.position.y = Block.transform.size.y * row;

		for (int column = 0; column < level->Resolution.x; column++) {

			Block.transform.position.x = Block.transform.size.x * column;

			switch (level->TileMap[CellId]) {

			case 0:
				break;

			case 1:
				level->CellArray.Add(Cell(1, Block.transform));

				if (CellId - 1 >= 0 && level->TileMap[CellId - 1] == 0 || CellId % level->Resolution.x == 0) {

					Line.transform.size.x = 1;
					Line.transform.size.y = Block.transform.size.y;
					Line.transform.position = Block.transform.position;
					GoArray.Add(Line);

				}

				if (level->TileMap[CellId + 1] == 0 || CellId % (level->Resolution.x - 1) == 0 && CellId != 0) {

					Line.transform.size.x = 1;
					Line.transform.size.y = Block.transform.size.y;
					Line.transform.position.x = Block.transform.position.x;
					Line.transform.position.x = Block.transform.position.x + Block.transform.size.x;
					GoArray.Add(Line);

				}

				if (CellId - level->Resolution.x > 0 && level->TileMap[CellId - level->Resolution.x] == 0) {

					Line.transform.size.y = 1;
					Line.transform.size.x = Block.transform.size.x;
					Line.transform.position = Block.transform.position;
					GoArray.Add(Line);

				}

				if (CellId + level->Resolution.x < level->Resolution.x * level->Resolution.y && level->TileMap[CellId + level->Resolution.x] == 0) {

					Line.transform.size.y = 1;
					Line.transform.size.x = Block.transform.size.x;
					Line.transform.position.y = Block.transform.position.y + Block.transform.size.y;
					GoArray.Add(Line);

				}

				break;

			default:
				Error("Illegal Cell type!");
				break;

			}

			CellId++;

		}

	}

}

void DrawLevel(Level level) {

	for (int i = 0; i != level.CellArray.GetSize(); i++) {

		switch (level.CellArray.members[i].type) {

			case 0:
				break;

			case 1:
				level.crystal.transform.position = level.CellArray.members[i].cellTransform.position;

				Draw(level.crystal);

				break;

			default:
				Error("Illegal cell type in CellArrayPtr");
				std::cout << level.CellArray.members[i].type << "\n";
				break;
		}

	}

}