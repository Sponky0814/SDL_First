#include "SDL.h"
#include <iostream>
#include <string>

using namespace ::std;

class Log {

	public:
		void Debug(std::string Log) {

			cout << "Log: " + Log << endl;

		}

};