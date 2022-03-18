#pragma once
#include "Mmath.h"
#include <Windows.h>

//Prints a variable/string to the console
template<class T>
void mLog(T Log) {
#ifdef _DEBUG
	std::cout << "Log: " << Log << "\n";
#endif
}

//Prints an error to the console
void Error(const char* Log, bool CheckErrorCache) {
#ifdef _DEBUG
	static FreeArray<const char*> ErrorCache;									//Stores already sent errors

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);				//Changes colour of text to red

	if (CheckErrorCache == true) {												//If 'CheckErrorCache' is true it checks if the error message has already been sent(if so it exits the function)

		for (int i = 0; i < ErrorCache.range(); i++) {							

			if (ErrorCache[i] == Log) {

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//Changes colour of text to white
				return;

			}

		}

	}

	std::cout << "Error: " << Log << "\n";										
	ErrorCache.insert(Log);														//Inserts error message intp the error cache

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);				//Changes colour of text to white
#endif
}
