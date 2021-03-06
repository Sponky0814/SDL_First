#pragma once
#include <iostream>
#include <vector>

#define elif else if

//Two dimentional vector
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

		void operator=(const Vector2<T>& other) {

			this->x = other.x;
			this->y = other.y;

			return;

		}

		bool operator!=(const Vector2<T>& other) const {

			if (x != other.x || y != other.y)
				return !(this == *other);
			else
				return (this == *other);

		}

};

//Four dimentional vector
template<typename T>
class Vector4 {

public:
	T a, b, c, d;

	Vector4() { a = false; b = false; c = false; d = false; }

	Vector4(T A, T B, T C, T D) {
		a = A; b = B; c = C; d = D;
	}

	void operator=(const Vector4& other) {

		this->a = other.a;
		this->b = other.b;
		this->c = other.c;
		this->d = other.d;

		return;

	}

};

template <class T>
class FreeArray {

	private:

		union FreeElement {

			T element;
			int next;

			FreeElement() {};
			~FreeElement() {};

		};

		int first_free;

		std::vector<FreeElement> data;

	public:

		/// Creates a new free list.
		FreeArray();

		/// Inserts an element to the free list and returns an index to it.
		int insert(const T& element);

		// Removes the nth element from the free list.
		void erase(int n);

		// Removes all elements from the free list.
		void clear();

		// Returns the range of valid indices.
		int range() const;

		// Returns the nth element.
		T& operator[](int n);

		// Returns the nth element.
		const T& operator[](int n) const;

};

template <class T>
FreeArray<T>::FreeArray() : first_free(-1) {}

template <class T>
int FreeArray<T>::insert(const T& element) {

	if (first_free != -1) {

		const int index = first_free;
		first_free = data[first_free].next;
		data[index].element = element;
		return index;

	} 
	else {

		FreeElement fe;
		fe.element = element;
		data.push_back(fe);
		return static_cast<int>(data.size() - 1);

	}

}

template <class T>
void FreeArray<T>::erase(int n) {

	data[n].next = first_free;
	first_free = n;

}

template <class T>
void FreeArray<T>::clear() {

	data.clear();
	first_free = -1;

}

template <class T>
int FreeArray<T>::range() const {

	return static_cast<int>(data.size());

}

template <class T>
T& FreeArray<T>::operator[](int n) {

	return data[n].element;

}

template <class T>
const T& FreeArray<T>::operator[](int n) const {

	return data[n].element;

}

