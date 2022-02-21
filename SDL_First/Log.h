#pragma once
#include "Mmath.h"
#include <Windows.h>

extern HANDLE ConsoleHandle;

void Debug(const char* Log) {

	std::cout << "Log: " << Log << "\n";

}

void Error(const char* Log) {

	static DyArray<const char*> ErrorCache;

	SetConsoleTextAttribute(ConsoleHandle, 12);

	for (int i = 0; i < ErrorCache.GetSize(); i++) {

		if (ErrorCache.members[i] == Log) {

			SetConsoleTextAttribute(ConsoleHandle, 15);
			return;

		}

	}

	std::cout << "Error: " << Log << "\n";
	ErrorCache.Add(Log);

	SetConsoleTextAttribute(ConsoleHandle, 15);

}