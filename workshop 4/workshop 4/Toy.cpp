#include <iostream>
#include <ostream>
#include "Toy.h"
#include <iomanip>
namespace seneca {
	const std::string& Toy::getName() const
	{
		return m_name;
	}
	Toy::Toy() : m_orderId(0), m_name(""),m_numOfItems(0),m_price(0.0), m_HST(0.13) {}
	
	void Toy::update(int numItems) 
	{
		this->m_numOfItems = numItems;
	}
	std::string Toy::trim(const std::string& str) {
		size_t s = str.find_first_not_of(" \n\r\t");
		size_t e = str.find_last_not_of(" \n\r\t");

		if ((string::npos == s) || (string::npos == e))
			return "";
		else
			return str.substr(s, e - s + 1);
	}
	Toy::Toy(const std::string& Toy) : m_orderId(0), m_name(""), m_numOfItems(0), m_price(0.0),m_HST(0.13)
	{
		const string delimiter = ":";
		string data = Toy;
		size_t index = data.find(delimiter);
		m_orderId = stoi(trim(data.substr(0, index)));
		data = data.erase(0, index + 1);
		index = data.find(delimiter);
		m_name = trim(data.substr(0, index));
		data = data.erase(0, index + 1);
		index = data.find(delimiter);
		m_numOfItems = stoi(trim(data.substr(0, index)));
		data = data.erase(0, index + 1);
		index = data.find(delimiter);
		m_price = stod(trim(data.substr(0, index)));
	}
	std::ostream& operator<<(std::ostream& os, const Toy& t)
	{
		double subtotal = t.m_price * t.m_numOfItems;
		double tax = subtotal * t.m_HST;
		double total = subtotal + tax;

		os << "Toy" << setw(8) << t.m_orderId << ": "
			<< setw(18) << right << t.m_name
			<< setw(3) << " " << t.m_numOfItems << " items"
			<< setw(8) << fixed << setprecision(2) << t.m_price
			<< " /item subtotal:" << setw(7) << subtotal
			<< " tax:" << setw(6) << tax
			<< " total:" << setw(7) << total;

		return os;
	}
}