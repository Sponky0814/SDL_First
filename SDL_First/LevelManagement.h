#pragma once
#include <Muon.h>

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
			crystal.texture = LoadTexture("Images/Rock.png");
			crystal.transform.size = { 60, 60 };

		}

		~Level() {}

		Level(int* tM, Vector2<int> r) {
			TileMap = tM; Resolution = r;

			crystal.name = "Crystal";
			crystal.texture = LoadTexture("Images/Rock.png");
			crystal.transform.size = { 60, 60 };

		}

};

	DyArray<Transform> BlockMap[256];

//####################
//Function definitions
//####################

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
	
					//This is awful
					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16)
						BlockMap[(int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128))].Add(Line);

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) || ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128))
						BlockMap[(int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128))].Add(Line);

				}

				//RIGHT
				if (level.TileMap[CellId + 1] == 0 ||
					CellId % (level.Resolution.x - 1) == 0 && CellId != 0) {

					Line.size.x = 1;
					Line.size.y = Block.transform.size.y;
					Line.position.x = Block.transform.position.x;
					Line.position.x = Block.transform.position.x + Block.transform.size.x;

					//This is awful
					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16)
						BlockMap[(int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128))].Add(Line);

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) || ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128))
						BlockMap[(int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128))].Add(Line);

				}

				//ABOVE
				if (CellId - level.Resolution.x > 0 &&
					level.TileMap[CellId - level.Resolution.x] == 0) {

					Line.size.y = 1;
					Line.size.x = Block.transform.size.x;
					Line.position = Block.transform.position;
					
					//This is awful
					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16)
						BlockMap[(int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128))].Add(Line);

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) || ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128))
						BlockMap[(int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128))].Add(Line);

				}

				//BELOW
				if (CellId + level.Resolution.x < level.Resolution.x * level.Resolution.y &&
					level.TileMap[CellId + level.Resolution.x] == 0) {

					Line.size.y = 1;
					Line.size.x = Block.transform.size.x;
					Line.position.y = Block.transform.position.y + Block.transform.size.y;
					
					//This is awful
					if ((int)Line.position.x / 128 < 16 && (int)Line.position.y / 128 < 16)
						BlockMap[(int)(ceil(Line.position.x / 128) + 32 * ceil(Line.position.y / 128))].Add(Line);

					if (ceil(Line.position.x / 128) != ceil((Line.position.x + Line.size.x) / 128) || ceil(Line.position.y / 128) != ceil((Line.position.y + Line.size.y) / 128))
						BlockMap[(int)(ceil((Line.position.x + Line.size.x) / 128) + 32 * ceil((Line.position.y + Line.size.y) / 128))].Add(Line);

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
