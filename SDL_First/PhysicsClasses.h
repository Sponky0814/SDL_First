#pragma once
#include <SDL_image.h>
#include "Mmath.h"
#include "Log.h"

//Stores stores two Vector2s used for storing position and size
class Transform {

	public:
		Vector2<float> position;
		Vector2<float> size;

		Transform() { position.x = 0; position.y = 0; size.x = 0; size.y = 0; }
		
		~Transform() {}

		Transform(float x, float y, float w, float h) {
			position = *new Vector2<float>(x, y); size = *new Vector2<float>(w, h);
		}

		void operator=(const Transform& other) {

			this->position.x = other.position.x;
			this->position.y = other.position.y;
			this->size.x = other.size.x;
			this->size.y = other.size.y;

			return;

		}

};

//Stores a transform, a Vector4 for storing collisions, a texture, the velocity of the object and it's name 
class gameObject {

	public:
		Transform transform{};
		Vector4<bool> collider;
		SDL_Texture* texture{};
		Vector2<float> velocity;

		const char* name = "Unknown";

		gameObject() {}

		void operator=(const gameObject& other) {

			this->transform = other.transform;
			this->collider = other.collider;
			this->texture = other.texture;
			this->velocity = other.velocity;

			return;

		}

};
