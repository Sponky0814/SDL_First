#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "PhysicsClasses.h"
#include "LevelClasses.h"
#include "LevelFunctions.h"
#include "RenderingClasses.h"
#include "Mmath.h"
#include "Log.h"

SDL_Rect Screen = { 0, 0, 1920, 1080 };
//SDL_Rect Screen = { 0, 0, 3440, 1440 };

SDL_Window* window = SDL_CreateWindow("Muon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen.w, Screen.h, SDL_WINDOW_SHOWN);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

#pragma region Variables

bool gameRunnig;

bool Input_d;
bool Input_a;

const size_t frameDelay = 17; // 60 fps
size_t frameStart;
size_t frameTime;

SDL_Event* event = new SDL_Event;

gameObject Player;

Level* Level1 = new Level(new int[576] {

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

	}, 32, 18 );

#pragma endregion

//Run code every frame
void Update() {
	
	mLog("App initialized");

	gameRunnig = true;

	while (gameRunnig) {

		//Frame cap
		frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - (Uint32)frameTime);
		
		//Take Input for y movement using windows API
		//because the SDL2 input system is garbage
		if (GetKeyState(VK_SPACE) & 0x8000 && Player.collider.b)
			Player.velocity.y = -16;

		//Take Input for x movement using windows API
		//because the SDL2 input system is garbage
		if (GetKeyState('A') & 0x8000) {

			if (!Player.collider.a) {

				switch (Player.collider.b) {

					case true:
						Player.velocity.x -= 1;

					case false:
						Player.velocity.x -= 0.8f;

				}

			}

			Input_a = true;

		}
		else
			Input_a = false;

		if (GetKeyState('D') & 0x8000) {

			if (!Player.collider.c) {

				switch (Player.collider.b) {
					
					case true:
						Player.velocity.x += 1;

					case false:
						Player.velocity.x += 0.8f;

				}

			}

			Input_d = true;

		}
		else
			Input_d = false;
		
		//Ground friction
		if (!Input_a && !Input_d && Player.collider.b)
			Player.velocity.x += (float)(-1 * Player.velocity.x);
		
		//air friction
		if (Player.velocity.x != 0 && !Player.collider.b)
			Player.velocity.x -= 0.1f * (Player.velocity.x / abs(Player.velocity.x));

		// Gravity
		if (Player.velocity.y < 16)
			Player.velocity.y += 1;

		// x Collision
		if (Player.collider.a && Player.velocity.x < 0 || Player.collider.c && Player.velocity.x > 0)
			Player.velocity.x = 0;

		// y Collision
		if (Player.collider.b && Player.velocity.y > 0)
			Player.velocity.y = 0;

		// cap speed
		if (abs(Player.velocity.x) > 5)
			Player.velocity.x = 5 * (Player.velocity.x / abs(Player.velocity.x));

		if (Input_a && Input_d && Player.collider.b)
			Player.velocity.x = 0;

		//Update x velocity
		Player.transform.position.x += (int)Player.velocity.x * 4;

		//Update y velocity
		Player.transform.position.y += (int)Player.velocity.y * 2;

		//Renders texure on screen
		//Player = GetCollisions(Player, *Level1);

		if (Player.transform.position.y + Player.transform.size.y > 1020) {

			Player.transform.position.y = 924.1f;
			Player.collider.b = true;

		}
		else
			Player.collider.b = false;

		SDL_RenderClear(renderer);

		DrawLevel(*Level1, renderer, Screen, Textures::Get());
		Draw(Player, renderer, Screen);

		SDL_RenderPresent(renderer);

		//Take SDL input
		while (SDL_PollEvent(event)) {
					
			if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE ||
				event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE) {

				gameRunnig = false;
				mLog("Quitting...");

			}

		}

	}

}

//Initializes Stuff
int main(int argc, char* argv[]) {

	//Set Console color to bright white
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	mLog("Initializing app...");

	SDL_Init(SDL_INIT_EVERYTHING);

	//Set Backround color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	Player.transform.size.x = 96;
	Player.transform.size.y = 96;
	Player.transform.position.x = 487;
	Player.transform.position.y = 700;
	Player.texture = LoadTexture("Images/Player.png", renderer);

	Update();

	mLog("Quit");

	return 0;

}
