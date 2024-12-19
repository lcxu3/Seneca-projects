#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using std::string;

namespace seneca {
	class SpellChecker {
	const static int size = 6;
		string m_badWords[size];
		string m_goodWords[size];
		int m_replacementCounts[size] = { 0 };
	public:
		SpellChecker(const char* filename);
		void operator()(std::string& text);
		void showStatistics(std::ostream& out) const;

	};

}
#endif // !SENECA_SPELLCHECKER_H
