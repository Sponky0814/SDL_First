#pragma once
#include <iostream>
#include <vector>

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

template <class T>
class FreeList {

	public:

		/// Creates a new free list.
		FreeList();

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

	private:

		union FreeElement {

			T element;
			int next;

		};

		std::vector<FreeElement> data;
		int first_free;

};

template <class T>
FreeList<T>::FreeList() : first_free(-1) {}

template <class T>
int FreeList<T>::insert(const T& element) {

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
void FreeList<T>::erase(int n) {

	data[n].next = first_free;
	first_free = n;

}

template <class T>
void FreeList<T>::clear() {

	data.clear();
	first_free = -1;

}

template <class T>
int FreeList<T>::range() const {

	return static_cast<int>(data.size());

}

template <class T>
T& FreeList<T>::operator[](int n) {

	return data[n].element;

}

template <class T>
const T& FreeList<T>::operator[](int n) const {

	return data[n].element;

}
