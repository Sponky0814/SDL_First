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

					if (TileMap[CellId] == 1) {

						cellArray[cellArrayTurn].cellTransform.position.x = Block.transform.position.x;
						cellArray[cellArrayTurn].cellTransform.position.y = Block.transform.position.y;
						cellArray[cellArrayTurn].type = 1;
						cellArrayTurn++;

						//LEFT
						if (CellId - 1 >= 0 && TileMap[CellId - 1] == 0 ||
							CellId % resX == 0) {

							Line.size.x = 1;
							Line.size.y = Block.transform.size.y;
							Line.position = Block.transform.position;

							if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16) {

								int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

								for (int i = 0; i < 128; i++) {

									if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

										BlockMap[b][i] = Line;
										break;

									}

								}

							}

							if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) ||
								ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128)) {

								int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

								for (int i = 0; i < 128; i++) {

									if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

										BlockMap[b][i] = Line;
										break;

									}

								}


							}

						}

						//RIGHT
						if (TileMap[CellId + 1] == 0 ||
							CellId % (resX - 1) == 0 && CellId != 0) {

							Line.size.x = 1;
							Line.size.y = Block.transform.size.y;
							Line.position.x = Block.transform.position.x;
							Line.position.x = Block.transform.position.x + Block.transform.size.x;

							if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16) {

								int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

								for (int i = 0; i < 128; i++) {

									if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

										BlockMap[b][i] = Line;
										break;

									}

								}

							}

							if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) ||
								ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128)) {

								int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

								for (int i = 0; i < 128; i++) {

									if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

										BlockMap[b][i] = Line;
										break;

									}

								}


							}

						}

						//ABOVE
						if (CellId - resX > 0 &&
							TileMap[CellId - resX] == 0) {

							Line.size.y = 1;
							Line.size.x = Block.transform.size.x;
							Line.position = Block.transform.position;

							if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16) {

								int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

								for (int i = 0; i < 128; i++) {

									if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

										BlockMap[b][i] = Line;
										break;

									}

								}

							}

							if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) ||
								ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128)) {

								int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

								for (int i = 0; i < 128; i++) {

									if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

										BlockMap[b][i] = Line;
										break;

									}

								}


							}

						}

						//BELOW
						if (CellId + resX < resX * resY &&
							TileMap[CellId + resX] == 0) {

							Line.size.y = 1;
							Line.size.x = Block.transform.size.x;
							Line.position.y = Block.transform.position.y + Block.transform.size.y;

							if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16) {

								int b = (int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128));

								for (int i = 0; i < 128; i++) {

									if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

										BlockMap[b][i] = Line;
										break;

									}

								}

							}

							if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) ||
								ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128)) {

								int b = (int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128));

								for (int i = 0; i < 128; i++) {

									if (BlockMap[b][i] == *new Transform(0, 0, 0, 0)) {

										BlockMap[b][i] = Line;
										break;

									}

								}


							}

						}

					}
					elif(TileMap[CellId] != 0) {

						Error("Illegal Cell type!");
						break;

					}

					CellId++;

				}

			}

		}

		int GetCellArraySize() { return size; }

};
