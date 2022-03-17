#pragma once
#include "PhysicsClasses.h"
#include "ObjectFunctions.h"
#include "Log.h"
#include "LevelClasses.h"
#include "RenderingClasses.h"
#include <fstream>
#include <iostream>

void DrawLevel(Level level, SDL_Renderer* renderer, SDL_Rect Resolution, Textures& textures) {

	gameObject Block;
	Block.transform.size.x = 60;
	Block.transform.size.y = 60;

	for (int i = 0; i != level.cellArray.range(); i++) {

		switch (level.cellArray[i].type) {

			case 0:
				break;

			case 1:
				
				for (int j = level.cellArray[i].cellTransform.size.x / 60;;) {

					Block.transform.position.x = level.cellArray[i].cellTransform.position.x;
					Block.transform.position.y = level.cellArray[i].cellTransform.position.y;
					Block.texture = textures.GetCrystal();
				
				}

				Draw(Block, renderer, Resolution);

				break;

			default:
				#ifdef _DEBUG
				Error("Illegal cell type in CellArrayPtr: ", false);
				std::cout << level.cellArray[i].type << "\n";
				#endif
				break;

		}

	}

}

/*
int* LoadLevel(const char* path, int resX, int resY) {

	std::fstream fStream;
	fStream.open(path);
	char cell;
	int* intArray = new int[resX * resY];

	for (int y = 0; y < resY; y++) {

		for (int y = 0; y < resX; y++) {

			fStream.get(cell);
			intArray[y * resY + resX] = atoi(&cell);
			fStream.ignore();

		}

	}

	fStream.close();

	return intArray;

}
*/