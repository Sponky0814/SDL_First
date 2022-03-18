#pragma once
#include <iostream>
#include "PhysicsClasses.h"
#include "Log.h"
#include "Mmath.h"

class Cell {

	public:
		int type = NULL;
		Transform cellTransform;

		Cell() {}

		Cell(Transform ct, int t) { cellTransform = ct; type = t; }

		Cell operator=(const Cell& other) { 
			
			this->cellTransform = other.cellTransform;
			this->type = other.type;

			return other; 
		
		}

};

class Level {

private:



public:

	FreeArray<Transform> BlockMap[256]; //Stores objects for collision in a grid

	FreeArray<Cell> cellArray; //Stores objects for rendering

	Level() {}

	~Level() {}

	Level(int* TileMap, const int& resX, const int& resY) { 
			
		Transform Block;

		Block.size.x = 60;
		int xMultiplyer = 1;
		Block.size.y = 60;

		Cell cellInsert;

		int j = 0;

		for (int row = 0; row < resY; row++) {

			Block.position.y = Block.size.y * row;

			for (int column = 0; column < resX; column++) {

				switch (TileMap[row * resX + column]) {

				case 1:

					Block.position.x = Block.size.x * column;

					if (row * resX + column == 544 || row * resX + column == 0)
					j = 0;

					if (TileMap[544] == 1)
						j = 0;

					j = 0;

					while(true) {

						if (TileMap[row * resX + column + 1] == 1 && column + 1 != resX) {

							xMultiplyer++;
							column++;
							j++;

						}
						else {

							break;

						}

					}

					cellInsert.cellTransform.position.x = Block.position.x;
					cellInsert.cellTransform.position.y = Block.position.y;
					cellInsert.cellTransform.size.x = Block.size.x * xMultiplyer;
					cellInsert.cellTransform.size.y = Block.size.y;
					cellInsert.type = 1;

					cellArray.insert(cellInsert);

					break;

				default:

					break;

				}

				xMultiplyer = 1;
				column++;

			}

		}

	}

};

/*

	
private:

	int size;

public:

	Transform BlockMap[256][128];

	Cell* cellArray;

	Level() {}

	~Level() {}

	Level(int* TileMap, int resX, int resY) { 
			
		size = 0;

		for (int i = 0; i < resX * resY; i++) {

			if (TileMap[i] != 0)
				size++;

		}

		//Increments every time a part of the cell array is changed
		int cellArrayTurn = 0;

		gameObject Block;
		Transform Line;

		Block.transform.size.x = 60;
		Block.transform.size.y = 60;

		int CellId = NULL;

		cellArray = new Cell[size];

		for (int row = 0; row < resY; row++) {

			Block.transform.position.y = Block.transform.size.y * row;

			for (int column = 0; column < resX; column++) {

				Block.transform.position.x = Block.transform.size.x * column;

				switch (TileMap[CellId]) {
					
				case 1:

					cellArray[cellArrayTurn].cellTransform.position.x = Block.transform.position.x;
					cellArray[cellArrayTurn].cellTransform.position.y = Block.transform.position.y;
					cellArray[cellArrayTurn].type = 1;
					cellArrayTurn++;

					//LEFT
					Line.size.x = 1;
					Line.size.y = Block.transform.size.y;
					Line.position = Block.transform.position;

					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16 && CellId - 1 >= 0 && TileMap[CellId - 1] == 0 ||
						(int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16 && CellId % resX == 0) {

						int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}

					}

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) && CellId - 1 >= 0 && TileMap[CellId - 1] == 0 ||
						ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) && CellId % resX == 0 ||
						ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128) && CellId - 1 >= 0 && TileMap[CellId - 1] == 0 ||
						ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128) && CellId % resX == 0) {

						int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}


					}

					//RIGHT
					Line.size.x = 1;
					Line.size.y = Block.transform.size.y;
					Line.position.x = Block.transform.position.x;
					Line.position.x = Block.transform.position.x + Block.transform.size.x;

					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16 && TileMap[CellId + 1] == 0 ||
						(int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16 && CellId % (resX - 1) == 0 && CellId != 0) {

						int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}

					}

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) && TileMap[CellId + 1] == 0 ||
						ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) && CellId % (resX - 1) == 0 && CellId != 0 ||
						ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128) && TileMap[CellId + 1] == 0 ||
						ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128) && CellId % (resX - 1) == 0 && CellId != 0) {

						int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}


					}

					//ABOVE
					Line.size.y = 1;
					Line.size.x = Block.transform.size.x;
					Line.position = Block.transform.position;

					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16 &&
						CellId - resX > 0 && TileMap[CellId - resX] == 0) {

						int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}

					}

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) && CellId - resX > 0 && TileMap[CellId - resX] == 0 ||
						ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128) && CellId - resX > 0 && TileMap[CellId - resX] == 0) {

						int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}


					}


					//BELOW
					Line.size.y = 1;
					Line.size.x = Block.transform.size.x;
					Line.position.y = Block.transform.position.y + Block.transform.size.y;

					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16 && 
						CellId + resX < resX * resY && TileMap[CellId + resX] == 0) {

						int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}

					}

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) &&
						CellId + resX < resX * resY && TileMap[CellId + resX] == 0 ||
						ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128) &&
						CellId + resX < resX * resY && TileMap[CellId + resX] == 0) {

						int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}


					}

					default:

					Error("Illegal Cell type!");
					break;

				}

				CellId++;

			}

		}

	}

		int GetCellArraySize() { return size; }

};*/
