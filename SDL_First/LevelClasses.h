#pragma once
#include <iostream>
#include "PhysicsClasses.h"
#include "Log.h"
#include "Mmath.h"

//Stores the transform and (int)type(Used for picking textures and properties)
class Cell {

public:
	int type = NULL;
	Transform cellTransform;

	Cell() {}

	Cell(Transform ct, int t) { cellTransform = ct; type = t; }

	void operator=(const Cell& other) { 
			
		this->cellTransform = other.cellTransform;
		this->type = other.type;

		return; 
		
	}

};

//Stores a BlockMap(Grid of square areas with objects inside them) and an array for storing Cell for rendering
class Level {

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

		for (int row = 0; row < resY; row++) {

			Block.position.y = Block.size.y * row;

			for (int column = 0; column < resX; column++) {

				switch (TileMap[row * resX + column]) {

				case 1:

					Block.position.x = Block.size.x * column;

					while(true) {

						if (TileMap[row * resX + column + 1] == 1 && column + 1 != resX) {

							xMultiplyer++;
							column++;

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
