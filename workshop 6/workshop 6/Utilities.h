#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <iostream>
#include <sstream>
#include <string>
#include "Person.h"
using namespace std;
namespace seneca {
	class Utilities {
		
	public:
		Person* buildInstance(istream& in);
	};
}
#endif // !SENECA_UTILITIES_H
