#pragma once
#include <Muon.h>
#include "PhysicsClasses.h"
#include "ObjectManagement.h"
#include "Log.h"
#include "LevelClasses.h"

extern Transform BlockMap[256][128];

void InitLevel(Level& level) {

	gameObject Block;
	Transform Line;

	Block.transform.size = { 60, 60 };
	int CellId = NULL;
	level.CellArray.members = new Cell;

	for (int row = 0; row < level.Resolution.y; row++) {

		Block.transform.position.y = Block.transform.size.y * row;

		for (int column = 0; column < level.Resolution.x; column++) {

			Block.transform.position.x = Block.transform.size.x * column;

			if (level.TileMap[CellId] == 1) {

				level.CellArray.Add(Cell(1, Block.transform));

				//LEFT
				if (CellId - 1 >= 0 && level.TileMap[CellId - 1] == 0 ||
					CellId % level.Resolution.x == 0) {
	
					Line.size.x = 1;
					Line.size.y = Block.transform.size.y;
					Line.position = Block.transform.position;

					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16) {

						int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == new Transform(0,0,0,0)) {

								BlockMap[b][i] = Line;
								break;
							
							}	

						}

					}

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) ||
						ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128)) {

						int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}


					}

				}

				//RIGHT
				if (level.TileMap[CellId + 1] == 0 ||
					CellId % (level.Resolution.x - 1) == 0 && CellId != 0) {

					Line.size.x = 1;
					Line.size.y = Block.transform.size.y;
					Line.position.x = Block.transform.position.x;
					Line.position.x = Block.transform.position.x + Block.transform.size.x;

					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16) {

						int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}

					}

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) ||
						ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128)) {

						int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}


					}

				}

				//ABOVE
				if (CellId - level.Resolution.x > 0 &&
					level.TileMap[CellId - level.Resolution.x] == 0) {

					Line.size.y = 1;
					Line.size.x = Block.transform.size.x;
					Line.position = Block.transform.position;
					
					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16) {

						int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}

					}

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) ||
						ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128)) {

						int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}


					}

				}

				//BELOW
				if (CellId + level.Resolution.x < level.Resolution.x * level.Resolution.y &&
					level.TileMap[CellId + level.Resolution.x] == 0) {

					Line.size.y = 1;
					Line.size.x = Block.transform.size.x;
					Line.position.y = Block.transform.position.y + Block.transform.size.y;
					
					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16) {

						int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}

					}

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) ||
						ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128)) {

						int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

						for (int i = 0; i < 128; i++) {

							if (BlockMap[b][i] == new Transform(0, 0, 0, 0)) {

								BlockMap[b][i] = Line;
								break;

							}

						}


					}

				}

			} 
			elif (level.TileMap[CellId] != 0) {

				Error("Illegal Cell type!");
				break;

			}

			CellId++;

		}

	}

}

void DrawLevel(Level level, SDL_Renderer* renderer, SDL_Rect Resolution) {

	for (int i = 0; i != level.CellArray.GetSize(); i++) {

		switch (level.CellArray.members[i].type) {

			case 0:
				break;

			case 1:
				crystal.transform.position = level.CellArray.members[i].cellTransform.position;

				Draw(crystal, renderer, Resolution);

				break;

			default:
				Error("Illegal cell type in CellArrayPtr");
				std::cout << level.CellArray.members[i].type << "\n";
				break;
		}

	}

}
