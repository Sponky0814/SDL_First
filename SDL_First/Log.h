#pragma once
#include "Mmath.h"
#include <Windows.h>

#define CheckErrorCache true

void Debug(const char* Log) {

	std::cout << "Log: " << Log << "\n";

}

void Debug(const float& Log) {

	std::cout << "Log: " << Log << "\n";

}

void Error(const char* Log) {

	static FreeList<const char*> ErrorCache;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

	for (int i = 0; i < ErrorCache.range(); i++) {

		if (ErrorCache[i] == Log && CheckErrorCache == true) {

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			return;

		}

	}

	std::cout << "Error: " << Log << "\n";
	ErrorCache.insert(Log);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

}
