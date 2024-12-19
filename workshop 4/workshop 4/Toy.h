#ifndef SENECA_TOY_H
#define SENECA_TOY_H
#include<string>
#include <ostream>
using namespace std;

namespace seneca {
	
	class Toy  {

		int m_orderId;
		string m_name;
		int m_numOfItems;
		double m_price;
		double m_HST;
		std::string trim(const std::string& str);
	
	public:
		Toy();
		void update(int numItems);
		Toy(const std::string& Toy);
		const string& getName() const;
		friend ostream &operator << (ostream &os, const Toy& t);
	};
}
#endif // !SENECA_TOY_H

