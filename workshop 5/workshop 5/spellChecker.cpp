
#include "spellChecker.h"
using namespace std;
namespace seneca {
	SpellChecker::SpellChecker(const char* filename)
	{
		fstream f(filename);
		if (!f.is_open()) {
			throw "Bad file names!";
		}
		int index = 0;
		std::string line;
		while (getline(f, line) && index < size) {
			std::istringstream iss(line);
			if (iss >> m_badWords[index] >> m_goodWords[index]) {
				++index;
			}
		}
		f.close();
	}

	void SpellChecker::operator()(std::string& text)
	{
		for (int i = 0; i < size; ++i) {
			size_t startPos = 0;
			while (startPos = text.find(m_badWords[i], startPos)) {
				text.replace(startPos, m_badWords[i].length(), m_goodWords[i]);
				++m_replacementCounts[i];
				startPos += m_goodWords[i].length();
			}
		}
	}

	void SpellChecker::showStatistics(std::ostream& out) const
	{
		for (int i = 0; i < 6; ++i) {
			out << std::right << std::setw(15) << m_badWords[i] << ": " << m_replacementCounts[i]  << std::endl;
		}
	}
}