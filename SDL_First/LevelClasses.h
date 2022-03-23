#pragma once
#include <iostream>
#include "PhysicsClasses.h"
#include "Log.h"
#include "Mmath.h"
#include "RenderingClasses.h"

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

	FreeArray<Transform>* BlockMap = new FreeArray<Transform>[1024]; //Stores objects for collision in a grid

	FreeArray<Cell> cellArray; //Stores objects for rendering

	Level() {}

	~Level() {}

	Level(int* TileMap, const int& resX, const int& resY, SDL_Renderer* renderer) { 
		
		Textures::AddTexture("crystal", "Images/Rock.png", renderer);
		Textures::AddTexture("red", "Images/Red.png", renderer);
		Textures::AddTexture("green", "Images/Green.png", renderer);
		Textures::AddTexture("blue", "Images/Blue.png", renderer);

		Transform Block;

		Block.size.x = 60;
		int xMultiplyer = 1;
		Block.size.y = 60;

		Cell cellInsert;

		int Len = 0;

		for (int row = 0; row < resY; row++) {

			Block.position.y = Block.size.y * row;

			for (int column = 0; column < resX; column++) {

				switch (TileMap[row * resX + column]) {

				case 1: case 2: case 3: case 4:

					Block.position.x = Block.size.x * column;

					while(true) {

						if (TileMap[row * resX + column + 1] == TileMap[row * resX + column] && column + 1 != resX) {

							xMultiplyer++;
							column++;
							Len++;

						}
						else {

							break;

						}

					}

					cellInsert.cellTransform.position.x = Block.position.x;
					cellInsert.cellTransform.position.y = Block.position.y;
					cellInsert.cellTransform.size.x = Block.size.x * xMultiplyer;
					cellInsert.cellTransform.size.y = Block.size.y;
					cellInsert.type = TileMap[row * resX + column];

					cellArray.insert(cellInsert);

					for (int i = 0; i <= ceil(Len * 60 / 128); i++) {

						BlockMap[(int)(ceil(cellInsert.cellTransform.position.x) / 128 + 32 * ceil(cellInsert.cellTransform.position.y / 128) + i)].insert(cellInsert.cellTransform);

					}

					break;

				default:

					break;

				}

				Len = 0;
				xMultiplyer = 1;
				column++;

			}

		}

	}

};
