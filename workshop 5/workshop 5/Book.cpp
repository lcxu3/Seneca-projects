
#include "Book.h"

namespace seneca {
	Book::Book() : author(""), m_title(""), m_country(""), m_year(0), m_price(0.0),description("") {}
	
	const std::string& Book::title() const
	{
		return m_title;
	}

	const std::string& Book::country() const
	{
		return m_country;
	}

	const size_t& Book::year() const
	{
		return m_year;
	}

	double& Book::price()
	{
		return m_price;
	}

	Book::Book(const std::string& strBook) : author(""), m_title(""), m_country(""), m_year(0), m_price(0.0), description("")
	{
		const string delimiter = ":";
		string data = strBook;
		size_t index = data.find(delimiter);
		author = stoi((data.substr(0, index)));
		data = data.erase(0, index);
		index = data.find(delimiter);
		m_title = stoi((data.substr(0, index)));
		data = data.erase(0, index);
		index = data.find(delimiter);
		m_country = stoi((data.substr(0, index)));
		data = data.erase(0, index);
		index = data.find(delimiter);
		m_year = stoi((data.substr(0, index)));
		data = data.erase(0, index);
		index = data.find(delimiter);
		m_price = stoi((data.substr(0, index)));
		data = data.erase(0, index);
		index = data.find(delimiter);
		description = stoi((data.substr(0, index)));
		data = data.erase(0, index);
		index = data.find(delimiter);
		
	}

	std::ostream& operator<<(std::ostream& os, Book b)
	{
		os << b.author << setw(20) << "|" <<
			b.m_title << setw(22) << "|" <<
			b.m_country << setw(5) << "|" <<
			b.m_year << setw(4) << "|" <<
			b.m_price << setw(6) << setprecision(2);
	}
}