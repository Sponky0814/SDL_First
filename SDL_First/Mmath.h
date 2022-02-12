#pragma once
#include <SDL.h>
#include <iostream>

SDL_Rect Screen = {0, 0, 1920, 1080};

//Create window and renderer
SDL_Window* window = SDL_CreateWindow("Muon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen.w, Screen.h, SDL_WINDOW_SHOWN);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

template<typename T>
class Vector2 {

	public:
		T x{};
		T y{};

		Vector2() {}

		Vector2(T X, T Y) {

			x = X;
			y = Y;

		}

		~Vector2() {}

		Vector2 operator=(Vector2<T>* other) const {

			return Vector2(x + other->x, y + other->y);

		}

};

template<typename T>
class DyArray {

	size_t size = 0;

	public:

		T* members;

		DyArray() { members = new T[size]; }

		~DyArray() {}

		void Add(T Input) {

			T* ArrayPtrTemp = new T[size + 1];

			for (int i = 0; i != size; i++) {

				ArrayPtrTemp[i] = members[i];

			}

			ArrayPtrTemp[size] = Input;

			members = ArrayPtrTemp;

			size++;

		}

	size_t GetSize() const { return this->size; }

};