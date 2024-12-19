#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <string>
#include "spellChecker.h"
#include <iostream>
#include <iomanip>

namespace seneca {
	class Book {
		std::string author;
		std::string m_title;
		std::string m_country;
		size_t m_year;
		double m_price;
		std::string description;

	public:
		Book();
		const std::string& title() const;
		const std::string& country() const;
		const size_t& year() const;
		double& price();
		Book(const std::string& strBook);
		friend std::ostream& operator<< (std::ostream& os, Book b);

};
	template <typename T>
	inline void fixSpelling(T& spellChecker) {
	spellChecker(description);

	}
}

#endif // !SENECA_BOOK_H

