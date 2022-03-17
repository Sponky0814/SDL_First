#pragma once
#include "Mmath.h"
#include <Windows.h>

void mLog(const char* Log) {
#ifdef _DEBUG
	std::cout << "Log: " << Log << "\n";
#endif
}

void mLog(const float& Log) {
#ifdef _DEBUG
	std::cout << "Log: " << Log << "\n";
#endif
}

void Error(const char* Log, bool CheckErrorCache) {

#ifdef _DEBUG

	static FreeArray<const char*> ErrorCache;

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
#endif
}
