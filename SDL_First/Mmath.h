#pragma once
#include <iostream>

#define elif else if

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

		Vector2* operator=(Vector2<T>* other) const {

			return other;

		}

		Vector2 operator=(const Vector2<T>& other) const {

			return other;

		}

		bool operator!=(const Vector2<T>* other) const {

			if (x != other->x || y != other->y)
				return !(this == *other);
			else
				return (this == *other);

		}

		bool operator!=(const Vector2<T>& other) const {

			if (x != other.x || y != other.y)
				return !(this == *other);
			else
				return (this == *other);

		}

};

template<typename T>
class DyArray {

	Uint16 size = 0;

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
