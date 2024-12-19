#include <iostream>
#include <fstream>
#include "StringSet.h"
#include <string>

namespace seneca {
	StringSet::StringSet() : strings(nullptr), numOfStrings(0){}

	StringSet::StringSet(const char* filename) : strings(nullptr), numOfStrings(0)
	{
		std::ifstream file(filename);
		file.open("gutenberg_shakespeare");

		std::string str;

		if (file.is_open()) {

			while (!file.eof()) {
				std::getline(file, str, ' ');
				if (file.eof()) {
					file.clear();
					file.seekg(0, std::ios::beg);

				}
			}


		}
		file.close();
		delete[] strings;
		strings = new std::string[numOfStrings];
		file.open(filename);
		for (int i = 0; i < numOfStrings; ++i) {
			std::getline(file, strings[i], ' ');
		}
	}
		
	StringSet::StringSet(const StringSet& ss)
	{
		numOfStrings = ss.numOfStrings;
		if (ss.strings != nullptr) {
			strings = ss.strings;
		}
		else {
			strings = nullptr;
		}
	}

	StringSet& StringSet::operator=(const StringSet& ss)
	{
		if (this != &ss) {
			numOfStrings = ss.numOfStrings;
			delete[] strings;
			if (ss.strings != nullptr) {
				strings = ss.strings;
			}
			else {
				strings = nullptr;
			}
		}
		return *this;
	}

	StringSet::~StringSet()
	{
		delete[] strings;
	}

	size_t StringSet::size() const
	{
		return numOfStrings;
	}

	std::string StringSet::operator[](size_t index) const
	{
		if (index < numOfStrings) {
			return strings[index];
		}

		else {
			return "";
		}
	}

	StringSet::StringSet(StringSet&& ss) noexcept : numOfStrings(ss.numOfStrings), strings(move(ss.strings))
	{}
	
	StringSet& StringSet::operator=(StringSet&& ss) noexcept
	{
		if (this != &ss) {
			delete[] strings;
			numOfStrings = ss.numOfStrings;
			strings = ss.strings;

			ss.numOfStrings = 0;
			ss.strings = nullptr;
		}
		return *this;
	}
}
