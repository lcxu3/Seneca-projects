#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#ifndef SENECA_MOVIE_H

using namespace std;
namespace seneca {
	class Movie {
		std::string m_title;
		int year;
		std::string descriptions;
	public:
		Movie();
		const std::string& title() const;
		Movie(const std::string& strMovie);
		friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
		template <typename T>
		void fixSpelling(T& spellChecker);
};
	template<typename T>
	inline void Movie::fixSpelling(T& spellChecker)
	{
		spellChecker(m_title);
		spellChecker(descriptions);
	}
}


#endif // !SENECA_MOVIE_H