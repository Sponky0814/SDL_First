#pragma once
#include <SDL_image.h>
#include "Mmath.h"
#include "Rendering.h"
#include "Log.h"

class Collider {

	public:
		bool a, b, c, d;

		Collider() { a = false; b = false; c = false; d = false; }

		Collider(bool A, bool B, bool C, bool D) {
			a = A; b = B; c = C; d = D;
		}

		Collider operator=(const Collider& other) const {

			return other;

		}

		Collider operator=(const Collider* other) const {

			return *other;

		}

};

class Transform {

	public:
		Vector2<float> position;
		Vector2<float> size;

		Transform() { position.x = 0; position.y = 0; size.x = 0; size.y = 0; }
		
		~Transform() {}

		Transform(float x, float y, float w, float h) {
			position = new Vector2<float>(x, y); size = new Vector2<float>(w, h);
		}

		bool operator==(const Transform& other) const {

			if (&other == nullptr) {

				Error("Reading from nullptr(transform)", false);
				return false;

			}
			else if (position.x == other.position.x && position.y == other.position.y && size.x == other.size.x && size.y == other.size.y)
				return true;
			else
				return false;

		}

		bool operator!=(const Transform& other) const {

			if (&other == nullptr) {

				Error("Reading from nullptr(transform)", false);
				return false;

			}
			else if (position.x == other.position.x || position.y == other.position.y || size.x == other.size.x || size.y == other.size.y)
				return false;
			else
				return true;

		}

		Transform operator = (const Transform& other) {

			this->position.x = other.position.x;
			this->position.y = other.position.y;
			this->size.x = other.size.x;
			this->size.y = other.size.y;

			return other;

		}

};

class gameObject {

	public:
		Transform transform{};
		Collider collider{};
		SDL_Texture* texture{};
		Vector2<float> velocity;

		const char* name = "Unknown";

		gameObject() {}

		gameObject(const char* NAME, Vector2<float> SIZE, const char* TEXTURE, SDL_Renderer* renderer) {

			name = NAME;
			texture = LoadTexture(TEXTURE, renderer);
			transform.size = SIZE;

		}

		gameObject operator=(const gameObject& other) const {

			return other;

		}

};
