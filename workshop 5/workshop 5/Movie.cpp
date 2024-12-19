#include <iostream>
#include <sstream>
#include <iomanip>
#include "Movie.h"

namespace seneca {
	Movie::Movie() : year(0){}

	const std::string& Movie::title() const
	{
		return m_title;
	}
	Movie::Movie(const std::string& strMovie) : year(0)
	{
		istringstream iss(strMovie);
		string token;
		getline(iss, token, ',');
		m_title = token;
		std::getline(iss, token, ',');
		year = std::stoi(token);
		std::getline(iss, descriptions);
	}
	std::ostream& operator<<(std::ostream& os, const Movie& movie)
	{
		os << std::setw(40) << std::left << movie.m_title << " | "
			<< std::setw(4) << std::right << movie.year << " | "
			<< movie.descriptions;
		return os;
	}
}