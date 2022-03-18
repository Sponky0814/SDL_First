#pragma once
#include "PhysicsClasses.h"
#include "ObjectFunctions.h"
#include "Log.h"
#include "LevelClasses.h"
#include "RenderingClasses.h"
#include <fstream>
#include <iostream>

//Draws a level on the screen
void DrawLevel(Level level, SDL_Renderer* renderer, SDL_Rect Resolution, Textures& textures) {

	gameObject Block;
	Block.transform.size.x = 60;
	Block.transform.size.y = 60;

	for (int i = 0; i != level.cellArray.range(); i++) {

		switch (level.cellArray[i].type) {

		case 0:
			break;

		case 1:
				
			for (int j = 0; j != level.cellArray[i].cellTransform.size.x / 60; j++) {

				Block.transform.position.x = level.cellArray[i].cellTransform.position.x + Block.transform.size.x * j;
				//mLog("#################");
				//mLog(Block.transform.position.x);
				Block.transform.position.y = level.cellArray[i].cellTransform.position.y;
				//mLog(Block.transform.position.y);
				//mLog("#################");
				Block.texture = textures.GetCrystal();
					

				//Sleep(250);
				Draw(Block, renderer, Resolution);
				//SDL_RenderPresent(renderer);
				//mLog(j);

			}

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