#pragma once
#include "PhysicsClasses.h"
#include "ObjectFunctions.h"
#include "Log.h"
#include "LevelClasses.h"
#include "RenderingClasses.h"
#include <fstream>
#include <iostream>

//Draws a level on the screen
void DrawLevel(Level level, SDL_Renderer* renderer, SDL_Rect Resolution) {

	static gameObject Block;
	Block.transform.size.x = 60;
	Block.transform.size.y = 60;

	for (int i = 0; i != level.cellArray.range(); i++) {

		switch (level.cellArray[i].type) {

		case 0:
			break;

		case 1:
				
			for (int j = 0; j != level.cellArray[i].cellTransform.size.x / 60; j++) {

				Block.transform.position.x = level.cellArray[i].cellTransform.position.x + 60 * j;
				Block.transform.position.y = level.cellArray[i].cellTransform.position.y;
				Block.texture = Textures::GetTexture("crystal");
				Draw(Block, renderer, Resolution);

			}

			break;

		case 2:

			for (int j = 0; j != level.cellArray[i].cellTransform.size.x / 60; j++) {

				Block.transform.position.x = level.cellArray[i].cellTransform.position.x + 60 * j;
				Block.transform.position.y = level.cellArray[i].cellTransform.position.y;
				Block.texture = Textures::GetTexture("red");
				Draw(Block, renderer, Resolution);

			}

		case 3:

			for (int j = 0; j != level.cellArray[i].cellTransform.size.x / 60; j++) {

				Block.transform.position.x = level.cellArray[i].cellTransform.position.x + 60 * j;
				Block.transform.position.y = level.cellArray[i].cellTransform.position.y;
				Block.texture = Textures::GetTexture("green");
				Draw(Block, renderer, Resolution);

			}

			break;

		case 4:

			for (int j = 0; j != level.cellArray[i].cellTransform.size.x / 60; j++) {

				Block.transform.position.x = level.cellArray[i].cellTransform.position.x + 60 * j;
				Block.transform.position.y = level.cellArray[i].cellTransform.position.y;
				Block.texture = Textures::GetTexture("blue");
				Draw(Block, renderer, Resolution);

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
