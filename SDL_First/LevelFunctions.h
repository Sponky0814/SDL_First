#pragma once
#include "PhysicsClasses.h"
#include "ObjectFunctions.h"
#include "Log.h"
#include "LevelClasses.h"
#include "RenderingClasses.h"

void DrawLevel(Level level, SDL_Renderer* renderer, SDL_Rect Resolution, Textures& textures) {

	gameObject Block;

	for (int i = 0; i != sizeof(level.cellArray); i++) {

		switch (level.cellArray[i].type) {

			case 0:
				break;

			case 1:
				
				Block.transform.size.x = 60;
				Block.transform.size.y = 60;
				Block.transform.position.x = level.cellArray[i].cellTransform.position.x;
				Block.transform.position.y = level.cellArray[i].cellTransform.position.x;
				Block.texture = LoadTexture("Images/Rock.png", renderer);

				Draw(Block, renderer, Resolution);

				break;

			default:
				Error("Illegal cell type in CellArrayPtr");
				std::cout << level.cellArray[i].type << "\n";
				break;
		}

	}

}
